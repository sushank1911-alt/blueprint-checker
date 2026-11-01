#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "question_paper.h"
#include "ai_helper.h"

void init_question_paper(QuestionPaper *qp) {
    memset(qp, 0, sizeof(QuestionPaper));
    strncpy(qp->institution, "RGM College of Engineering and Technology (Autonomous), Nandyal", MAX_STR - 1);
    strncpy(qp->department, "Department of CSE (AI & ML)", MAX_STR - 1);
    strncpy(qp->subject_name, "Data Structures and Algorithms", MAX_STR - 1);
    strncpy(qp->exam_name, "II B.Tech I Sem End Examinations (AY 2026-27)", MAX_STR - 1);
    qp->total_marks = 0;
    qp->question_count = 0;
}

int add_question(QuestionPaper *qp, const char *q_no, const char *content, int unit, int co_number, const char *topic, int cog_level, int marks) {
    if (qp->question_count >= MAX_QUESTIONS) {
        printf("%sError: Maximum question limit reached!%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    Question *q = &qp->questions[qp->question_count];
    strncpy(q->q_no, q_no, sizeof(q->q_no) - 1);
    strncpy(q->content, content, sizeof(q->content) - 1);
    q->unit = unit;
    q->co_number = co_number;
    strncpy(q->topic, topic, sizeof(q->topic) - 1);
    q->cognitive_level = cog_level;
    q->marks = marks;

    qp->question_count++;
    calculate_question_paper_total_marks(qp);

    // AI/ML feature: verify Bloom's action verb alignment
    ai_verify_question_alignment(q);
    return 1;
}

int calculate_question_paper_total_marks(QuestionPaper *qp) {
    int sum = 0;
    for (int i = 0; i < qp->question_count; i++) {
        sum += qp->questions[i].marks;
    }
    qp->total_marks = sum;
    return sum;
}

void view_question_paper(const QuestionPaper *qp) {
    printf("\n========================================================================================================================\n");
    printf("                               %sACTUAL QUESTION PAPER - INVENTORY (WITH CO MAPPING)%s\n", COLOR_CYAN, COLOR_RESET);
    printf(" Institution : %s\n", qp->institution);
    printf(" Department  : %s\n", qp->department);
    printf(" Subject     : %s | Exam: %s\n", qp->subject_name, qp->exam_name);
    printf("========================================================================================================================\n");
    printf("| %-6s | %-6s | %-5s | %-44s | %-13s | %-5s |\n",
           "Q.No", "Unit", "CO", "Question Content", "Cognitive Lvl", "Marks");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    if (qp->question_count == 0) {
        printf("| No questions registered in this question paper yet!                                                                   |\n");
    } else {
        for (int i = 0; i < qp->question_count; i++) {
            const Question *q = &qp->questions[i];
            printf("| %-6s | Unit %-1d | CO %-1d | %-44.44s | %-13s | %-5d |\n",
                   q->q_no,
                   q->unit,
                   q->co_number,
                   q->content,
                   get_cognitive_name(q->cognitive_level),
                   q->marks);
        }
    }
    printf("========================================================================================================================\n");
    printf(" Total Questions: %-3d | Total Accumulated Marks: %s%d Marks%s\n",
           qp->question_count, COLOR_BOLD, qp->total_marks, COLOR_RESET);
    printf("========================================================================================================================\n");
}

int modify_question(QuestionPaper *qp, int index) {
    if (index < 1 || index > qp->question_count) {
        printf("%sError: Invalid question index.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    Question *q = &qp->questions[index - 1];
    printf("Modifying Question %s:\n", q->q_no);

    printf("Enter new Question No (e.g. Q1a): ");
    scanf("%15s", q->q_no);

    printf("Enter Question Content: ");
    while (getchar() != '\n');
    if (fgets(q->content, sizeof(q->content), stdin)) {
        q->content[strcspn(q->content, "\r\n")] = '\0';
    }

    printf("Enter Unit (1-5): ");
    if (scanf("%d", &q->unit) != 1) return 0;

    printf("Enter Course Outcome CO (1-5): ");
    if (scanf("%d", &q->co_number) != 1) return 0;

    printf("Enter Topic Name: ");
    while (getchar() != '\n');
    if (fgets(q->topic, sizeof(q->topic), stdin)) {
        q->topic[strcspn(q->topic, "\r\n")] = '\0';
    }

    printf("Enter Cognitive Level (1:L1 .. 6:L6): ");
    if (scanf("%d", &q->cognitive_level) != 1) return 0;

    printf("Enter Marks: ");
    if (scanf("%d", &q->marks) != 1) return 0;

    calculate_question_paper_total_marks(qp);
    ai_verify_question_alignment(q);
    printf("%sQuestion %s updated successfully!%s\n", COLOR_GREEN, q->q_no, COLOR_RESET);
    return 1;
}

int delete_question(QuestionPaper *qp, int index) {
    if (index < 1 || index > qp->question_count) {
        printf("%sError: Invalid question index.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    int idx = index - 1;
    for (int i = idx; i < qp->question_count - 1; i++) {
        qp->questions[i] = qp->questions[i + 1];
    }
    qp->question_count--;
    calculate_question_paper_total_marks(qp);
    printf("%sQuestion deleted successfully.%s\n", COLOR_GREEN, COLOR_RESET);
    return 1;
}

int save_question_paper_to_file(const QuestionPaper *qp, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("%sError opening file %s for writing!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%d\n",
            qp->institution, qp->department, qp->subject_name, qp->exam_name,
            qp->total_marks, qp->question_count);

    for (int i = 0; i < qp->question_count; i++) {
        const Question *q = &qp->questions[i];
        fprintf(fp, "%s#%s#%d#%d#%s#%d#%d\n",
                q->q_no, q->content, q->unit, q->co_number, q->topic, q->cognitive_level, q->marks);
    }

    fclose(fp);
    printf("%sQuestion paper saved successfully to '%s'.%s\n", COLOR_GREEN, filename, COLOR_RESET);
    return 1;
}

int load_question_paper_from_file(QuestionPaper *qp, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("%sError opening file %s for reading!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    init_question_paper(qp);
    char line[MAX_TEXT * 2];

    if (fgets(qp->institution, sizeof(qp->institution), fp)) qp->institution[strcspn(qp->institution, "\r\n")] = '\0';
    if (fgets(qp->department, sizeof(qp->department), fp)) qp->department[strcspn(qp->department, "\r\n")] = '\0';
    if (fgets(qp->subject_name, sizeof(qp->subject_name), fp)) qp->subject_name[strcspn(qp->subject_name, "\r\n")] = '\0';
    if (fgets(qp->exam_name, sizeof(qp->exam_name), fp)) qp->exam_name[strcspn(qp->exam_name, "\r\n")] = '\0';

    if (fscanf(fp, "%d\n%d\n", &qp->total_marks, &qp->question_count) != 2) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < qp->question_count; i++) {
        Question *q = &qp->questions[i];
        if (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\r\n")] = '\0';
            char *tok = strtok(line, "#");
            if (tok) strncpy(q->q_no, tok, sizeof(q->q_no) - 1);

            tok = strtok(NULL, "#");
            if (tok) strncpy(q->content, tok, sizeof(q->content) - 1);

            tok = strtok(NULL, "#");
            if (tok) q->unit = atoi(tok);

            tok = strtok(NULL, "#");
            if (tok) q->co_number = atoi(tok);

            tok = strtok(NULL, "#");
            if (tok) strncpy(q->topic, tok, sizeof(q->topic) - 1);

            tok = strtok(NULL, "#");
            if (tok) q->cognitive_level = atoi(tok);

            tok = strtok(NULL, "#");
            if (tok) q->marks = atoi(tok);
        }
    }

    fclose(fp);
    printf("%sLoaded %d questions from '%s'.%s\n", COLOR_GREEN, qp->question_count, filename, COLOR_RESET);
    return 1;
}

void load_default_rgm_question_paper(QuestionPaper *qp, int flawed_scenario) {
    init_question_paper(qp);

    if (!flawed_scenario) {
        // SCENARIO 1: Perfectly Compliant 70 Marks Paper with CO1 to CO5
        add_question(qp, "Q1(a)", "Define asymptotic notations and state their significance in algorithm analysis.", 1, 1, "Linear Data Structures & Arrays", COG_L1, 4);
        add_question(qp, "Q1(b)", "Implement insertion and deletion operations in a Doubly Linked List with code.", 1, 1, "Singly & Doubly Linked Lists", COG_L3, 10);

        add_question(qp, "Q2(a)", "Explain the postfix expression evaluation using stack with an example.", 2, 2, "Stack Operations & Applications", COG_L2, 4);
        add_question(qp, "Q2(b)", "Solve the circular queue implementation and demonstrate handling of boundary conditions.", 2, 2, "Queue & Circular Queue Logic", COG_L3, 10);

        add_question(qp, "Q3(a)", "Describe in-order, pre-order, and post-order traversals of a binary tree.", 3, 3, "Binary Tree Traversals", COG_L2, 4);
        add_question(qp, "Q3(b)", "Analyze LL, RR, LR, and RL rotations required to balance an AVL tree after insertions.", 3, 3, "AVL Trees & BST Balancing", COG_L4, 10);

        add_question(qp, "Q4(a)", "Demonstrate Breadth First Search (BFS) graph traversal algorithm with a trace.", 4, 4, "Graph Representations (BFS/DFS)", COG_L3, 6);
        add_question(qp, "Q4(b)", "Analyze Dijkstra's single source shortest path algorithm on a weighted directed graph.", 4, 4, "Shortest Paths (Dijkstra/Prims)", COG_L4, 8);

        add_question(qp, "Q5(a)", "Discuss open addressing techniques for hash table collision resolution.", 5, 5, "Hashing Techniques & Collisions", COG_L2, 4);
        add_question(qp, "Q5(b)", "Evaluate the best, average, and worst-case time complexities of Quick Sort vs Merge Sort.", 5, 5, "Search & Sorting Complexities", COG_L5, 10);

        printf("%sSample 1: PERFECTLY COMPLIANT Question Paper loaded (70 Marks, 10 Questions, CO1-CO5).%s\n",
               COLOR_GREEN, COLOR_RESET);
    } else {
        // SCENARIO 2: Flawed Paper with deliberate flaws (over-allocation, wrong Bloom levels, missing Unit 5/CO5)
        add_question(qp, "Q1(a)", "Define asymptotic notations and state their significance.", 1, 1, "Linear Data Structures & Arrays", COG_L1, 6);
        add_question(qp, "Q1(b)", "Explain singly linked list insertion with algorithms.", 1, 1, "Singly & Doubly Linked Lists", COG_L2, 12);

        add_question(qp, "Q2(a)", "Explain stack operations and their applications in detail.", 2, 2, "Stack Operations & Applications", COG_L2, 4);
        add_question(qp, "Q2(b)", "Solve queue operations and describe stack operations and their applications.", 2, 2, "Queue & Circular Queue Logic", COG_L3, 10); // Redundant phrasing with Q2(a)!

        add_question(qp, "Q3(a)", "List tree traversal types.", 3, 3, "Binary Tree Traversals", COG_L1, 4);
        add_question(qp, "Q3(b)", "Define AVL tree properties.", 3, 3, "AVL Trees & BST Balancing", COG_L1, 8);

        add_question(qp, "Q4(a)", "Demonstrate BFS graph traversal.", 4, 4, "Graph Representations (BFS/DFS)", COG_L3, 6);
        add_question(qp, "Q4(b)", "Analyze Dijkstra's algorithm on a graph.", 4, 4, "Graph Representations (BFS/DFS)", COG_L4, 8);

        printf("%sSample 2: FLAWED Question Paper loaded (58 Marks, CO5 Missing, Redundancy Injected).%s\n",
               COLOR_YELLOW, COLOR_RESET);
    }
}
