#include <stdio.h>
#include <string.h>
#include "blueprint.h"

void init_blueprint(Blueprint *bp) {
    memset(bp, 0, sizeof(Blueprint));
    strncpy(bp->institution, "RGM College of Engineering and Technology (Autonomous), Nandyal", MAX_STR - 1);
    strncpy(bp->department, "Department of CSE (AI & ML)", MAX_STR - 1);
    strncpy(bp->subject_name, "Data Structures and Algorithms", MAX_STR - 1);
    strncpy(bp->exam_name, "II B.Tech I Sem End Examinations (AY 2026-27)", MAX_STR - 1);
    bp->total_expected_marks = 0;
    bp->rule_count = 0;
}

int add_blueprint_rule(Blueprint *bp, int unit, int co_number, const char *topic, int cog_level, int exp_q, int exp_marks) {
    if (bp->rule_count >= MAX_RULES) {
        printf("%sError: Blueprint rule limit reached!%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    BlueprintItem *item = &bp->rules[bp->rule_count];
    item->rule_id = bp->rule_count + 1;
    item->unit = unit;
    item->co_number = co_number;
    strncpy(item->topic, topic, MAX_STR - 1);
    item->cognitive_level = cog_level;
    item->expected_questions = exp_q;
    item->expected_marks = exp_marks;

    bp->rule_count++;
    calculate_blueprint_total_marks(bp);
    return 1;
}

int calculate_blueprint_total_marks(Blueprint *bp) {
    int total = 0;
    for (int i = 0; i < bp->rule_count; i++) {
        total += bp->rules[i].expected_marks;
    }
    bp->total_expected_marks = total;
    return total;
}

void view_blueprint(const Blueprint *bp) {
    printf("\n========================================================================================================\n");
    printf("                  %sEXAMINATION BLUEPRINT - REFERENCE STANDARD (OBE & BLOOM'S)%s\n", COLOR_CYAN, COLOR_RESET);
    printf(" Institution : %s\n", bp->institution);
    printf(" Department  : %s\n", bp->department);
    printf(" Subject     : %s | Exam: %s\n", bp->subject_name, bp->exam_name);
    printf("========================================================================================================\n");
    printf("| %-4s | %-6s | %-5s | %-28s | %-13s | %-7s | %-6s |\n",
           "ID", "Unit", "CO", "Topic", "Cognitive Lvl", "Exp Qs", "Marks");
    printf("--------------------------------------------------------------------------------------------------------\n");

    if (bp->rule_count == 0) {
        printf("| No blueprint rules defined yet!                                                                      |\n");
    } else {
        for (int i = 0; i < bp->rule_count; i++) {
            const BlueprintItem *it = &bp->rules[i];
            printf("| %-4d | Unit %-1d | CO %-1d | %-28.28s | %-13s | %-7d | %-6d |\n",
                   it->rule_id,
                   it->unit,
                   it->co_number,
                   it->topic,
                   get_cognitive_name(it->cognitive_level),
                   it->expected_questions,
                   it->expected_marks);
        }
    }
    printf("========================================================================================================\n");
    printf(" Total Rules: %-3d | Prescribed Total Marks: %s%d Marks%s\n",
           bp->rule_count, COLOR_BOLD, bp->total_expected_marks, COLOR_RESET);
    printf("========================================================================================================\n");
}

int modify_blueprint_rule(Blueprint *bp, int rule_id) {
    if (rule_id < 1 || rule_id > bp->rule_count) {
        printf("%sError: Invalid Rule ID.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }
    BlueprintItem *it = &bp->rules[rule_id - 1];

    printf("Modifying Rule #%d (Current: Unit %d, CO %d, Topic: %s, Marks: %d):\n",
           rule_id, it->unit, it->co_number, it->topic, it->expected_marks);

    printf("Enter new Unit (1-5): ");
    if (scanf("%d", &it->unit) != 1) return 0;

    printf("Enter new Course Outcome CO (1-5): ");
    if (scanf("%d", &it->co_number) != 1) return 0;

    printf("Enter new Topic Name: ");
    while (getchar() != '\n');
    if (fgets(it->topic, sizeof(it->topic), stdin)) {
        it->topic[strcspn(it->topic, "\r\n")] = '\0';
    }

    printf("Enter new Cognitive Level (1:L1 .. 6:L6): ");
    if (scanf("%d", &it->cognitive_level) != 1) return 0;

    printf("Enter new Expected Question Count: ");
    if (scanf("%d", &it->expected_questions) != 1) return 0;

    printf("Enter new Expected Marks: ");
    if (scanf("%d", &it->expected_marks) != 1) return 0;

    calculate_blueprint_total_marks(bp);
    printf("%sRule #%d updated successfully!%s\n", COLOR_GREEN, rule_id, COLOR_RESET);
    return 1;
}

int delete_blueprint_rule(Blueprint *bp, int rule_id) {
    if (rule_id < 1 || rule_id > bp->rule_count) {
        printf("%sError: Invalid Rule ID.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    int idx = rule_id - 1;
    for (int i = idx; i < bp->rule_count - 1; i++) {
        bp->rules[i] = bp->rules[i + 1];
        bp->rules[i].rule_id = i + 1;
    }
    bp->rule_count--;
    calculate_blueprint_total_marks(bp);
    printf("%sRule #%d deleted successfully.%s\n", COLOR_GREEN, rule_id, COLOR_RESET);
    return 1;
}

int save_blueprint_to_file(const Blueprint *bp, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("%sError opening file %s for writing!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%d\n",
            bp->institution, bp->department, bp->subject_name, bp->exam_name,
            bp->total_expected_marks, bp->rule_count);

    for (int i = 0; i < bp->rule_count; i++) {
        const BlueprintItem *it = &bp->rules[i];
        fprintf(fp, "%d,%d,%d,%s,%d,%d,%d\n",
                it->rule_id, it->unit, it->co_number, it->topic,
                it->cognitive_level, it->expected_questions, it->expected_marks);
    }

    fclose(fp);
    printf("%sBlueprint saved successfully to '%s'.%s\n", COLOR_GREEN, filename, COLOR_RESET);
    return 1;
}

int load_blueprint_from_file(Blueprint *bp, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("%sError opening file %s for reading!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    init_blueprint(bp);
    char line[MAX_TEXT];

    if (fgets(bp->institution, sizeof(bp->institution), fp)) bp->institution[strcspn(bp->institution, "\r\n")] = '\0';
    if (fgets(bp->department, sizeof(bp->department), fp)) bp->department[strcspn(bp->department, "\r\n")] = '\0';
    if (fgets(bp->subject_name, sizeof(bp->subject_name), fp)) bp->subject_name[strcspn(bp->subject_name, "\r\n")] = '\0';
    if (fgets(bp->exam_name, sizeof(bp->exam_name), fp)) bp->exam_name[strcspn(bp->exam_name, "\r\n")] = '\0';

    if (fscanf(fp, "%d\n%d\n", &bp->total_expected_marks, &bp->rule_count) != 2) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < bp->rule_count; i++) {
        BlueprintItem *it = &bp->rules[i];
        if (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\r\n")] = '\0';
            sscanf(line, "%d,%d,%d,%[^,],%d,%d,%d",
                   &it->rule_id, &it->unit, &it->co_number, it->topic,
                   &it->cognitive_level, &it->expected_questions, &it->expected_marks);
        }
    }

    fclose(fp);
    printf("%sLoaded %d blueprint rules from '%s'.%s\n", COLOR_GREEN, bp->rule_count, filename, COLOR_RESET);
    return 1;
}

void load_default_rgm_blueprint(Blueprint *bp) {
    init_blueprint(bp);
    // Standard 70-marks autonomous question paper distribution across 5 units & 5 COs (14 marks per unit/CO)
    add_blueprint_rule(bp, 1, 1, "Linear Data Structures & Arrays", COG_L1, 1, 4);
    add_blueprint_rule(bp, 1, 1, "Singly & Doubly Linked Lists",    COG_L3, 1, 10);

    add_blueprint_rule(bp, 2, 2, "Stack Operations & Applications", COG_L2, 1, 4);
    add_blueprint_rule(bp, 2, 2, "Queue & Circular Queue Logic",    COG_L3, 1, 10);

    add_blueprint_rule(bp, 3, 3, "Binary Tree Traversals",          COG_L2, 1, 4);
    add_blueprint_rule(bp, 3, 3, "AVL Trees & BST Balancing",       COG_L4, 1, 10);

    add_blueprint_rule(bp, 4, 4, "Graph Representations (BFS/DFS)", COG_L3, 1, 6);
    add_blueprint_rule(bp, 4, 4, "Shortest Paths (Dijkstra/Prims)", COG_L4, 1, 8);

    add_blueprint_rule(bp, 5, 5, "Hashing Techniques & Collisions", COG_L2, 1, 4);
    add_blueprint_rule(bp, 5, 5, "Search & Sorting Complexities",   COG_L5, 1, 10);

    printf("%sDefault RGM College 70-Marks Blueprint loaded (5 Units, 5 COs, 10 Rules, Total: %d Marks).%s\n",
           COLOR_GREEN, bp->total_expected_marks, COLOR_RESET);
}
