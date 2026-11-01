#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analysis.h"

static void init_report_structure(AuditReport *report) {
    memset(report, 0, sizeof(AuditReport));
    report->num_units = 5;

    for (int u = 1; u <= MAX_UNITS; u++) {
        report->unit_stats[u - 1].id = u;
        snprintf(report->unit_stats[u - 1].name, MAX_STR, "Unit %d", u);
    }

    for (int co = 1; co <= MAX_COS; co++) {
        report->co_stats[co].id = co;
        snprintf(report->co_stats[co].name, MAX_STR, "CO %d", co);
    }

    const char *bloom_names[] = {"None", "L1 (Remember)", "L2 (Understand)", "L3 (Apply)", "L4 (Analyze)", "L5 (Evaluate)", "L6 (Create)"};
    for (int lvl = 1; lvl <= 6; lvl++) {
        report->cog_stats[lvl].id = lvl;
        strncpy(report->cog_stats[lvl].name, bloom_names[lvl], MAX_STR - 1);
    }
}

void organize_and_analyze_data(const Blueprint *bp, const QuestionPaper *qp, AuditReport *report) {
    init_report_structure(report);

    strncpy(report->subject, bp->subject_name, MAX_STR - 1);
    strncpy(report->exam, bp->exam_name, MAX_STR - 1);
    report->total_expected_marks = bp->total_expected_marks;
    report->total_actual_marks = qp->total_marks;

    int max_unit = 5;

    // 1. Organize Blueprint expectations
    for (int i = 0; i < bp->rule_count; i++) {
        const BlueprintItem *it = &bp->rules[i];
        if (it->unit > max_unit && it->unit <= MAX_UNITS) max_unit = it->unit;

        if (it->unit >= 1 && it->unit <= MAX_UNITS) {
            report->unit_stats[it->unit - 1].expected_marks += it->expected_marks;
            report->unit_stats[it->unit - 1].expected_questions += it->expected_questions;
        }

        if (it->co_number >= 1 && it->co_number <= MAX_COS) {
            report->co_stats[it->co_number].expected_marks += it->expected_marks;
            report->co_stats[it->co_number].expected_questions += it->expected_questions;
        }

        if (it->cognitive_level >= 1 && it->cognitive_level <= 6) {
            report->cog_stats[it->cognitive_level].expected_marks += it->expected_marks;
            report->cog_stats[it->cognitive_level].expected_questions += it->expected_questions;
        }
        report->total_expected_questions += it->expected_questions;
    }

    // 2. Organize Question Paper actual distributions
    float weighted_diff_sum = 0.0f;
    for (int i = 0; i < qp->question_count; i++) {
        const Question *q = &qp->questions[i];
        if (q->unit > max_unit && q->unit <= MAX_UNITS) max_unit = q->unit;

        if (q->unit >= 1 && q->unit <= MAX_UNITS) {
            report->unit_stats[q->unit - 1].actual_marks += q->marks;
            report->unit_stats[q->unit - 1].actual_questions += 1;
        }

        if (q->co_number >= 1 && q->co_number <= MAX_COS) {
            report->co_stats[q->co_number].actual_marks += q->marks;
            report->co_stats[q->co_number].actual_questions += 1;
        }

        if (q->cognitive_level >= 1 && q->cognitive_level <= 6) {
            report->cog_stats[q->cognitive_level].actual_marks += q->marks;
            report->cog_stats[q->cognitive_level].actual_questions += 1;
            weighted_diff_sum += (float)(q->cognitive_level * q->marks);
        }
    }
    report->total_actual_questions = qp->question_count;
    report->num_units = max_unit;

    // Calculate Difficulty Index
    if (qp->total_marks > 0) {
        report->difficulty_index = weighted_diff_sum / (float)qp->total_marks;
    } else {
        report->difficulty_index = 0.0f;
    }

    if (report->difficulty_index < 2.2f) {
        strncpy(report->difficulty_rating, "EASY (Heavy Lower-Order Thinking)", MAX_STR - 1);
    } else if (report->difficulty_index <= 3.8f) {
        strncpy(report->difficulty_rating, "WELL-BALANCED (Recommended for Autonomous Exams)", MAX_STR - 1);
    } else {
        strncpy(report->difficulty_rating, "HIGHLY CHALLENGING (Excessive HOTS)", MAX_STR - 1);
    }

    // 3. Compute differences
    for (int u = 0; u < report->num_units; u++) {
        report->unit_stats[u].marks_diff = report->unit_stats[u].actual_marks - report->unit_stats[u].expected_marks;
        report->unit_stats[u].question_diff = report->unit_stats[u].actual_questions - report->unit_stats[u].expected_questions;
    }

    for (int co = 1; co <= MAX_COS; co++) {
        report->co_stats[co].marks_diff = report->co_stats[co].actual_marks - report->co_stats[co].expected_marks;
        report->co_stats[co].question_diff = report->co_stats[co].actual_questions - report->co_stats[co].expected_questions;
    }

    for (int lvl = 1; lvl <= 6; lvl++) {
        report->cog_stats[lvl].marks_diff = report->cog_stats[lvl].actual_marks - report->cog_stats[lvl].expected_marks;
        report->cog_stats[lvl].question_diff = report->cog_stats[lvl].actual_questions - report->cog_stats[lvl].expected_questions;
    }
}

void display_unit_wise_analysis(const AuditReport *report) {
    printf("\n========================================================================================\n");
    printf("              %sMODULE 3: UNIT-WISE DATA ANALYSIS SUMMARY%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");
    printf("| %-8s | %-10s | %-10s | %-10s | %-10s | %-10s |\n",
           "Unit", "Exp Qs", "Act Qs", "Exp Marks", "Act Marks", "Marks Diff");
    printf("----------------------------------------------------------------------------------------\n");

    for (int u = 0; u < report->num_units; u++) {
        const CategoryStat *st = &report->unit_stats[u];
        char diff_str[32];
        if (st->marks_diff > 0) {
            snprintf(diff_str, sizeof(diff_str), "%s+%d (Over)%s", COLOR_YELLOW, st->marks_diff, COLOR_RESET);
        } else if (st->marks_diff < 0) {
            snprintf(diff_str, sizeof(diff_str), "%s%d (Under)%s", COLOR_RED, st->marks_diff, COLOR_RESET);
        } else {
            snprintf(diff_str, sizeof(diff_str), "%s0 (Match)%s", COLOR_GREEN, COLOR_RESET);
        }

        printf("| %-8s | %-10d | %-10d | %-10d | %-10d | %-19s |\n",
               st->name, st->expected_questions, st->actual_questions,
               st->expected_marks, st->actual_marks, diff_str);
    }
    printf("========================================================================================\n");
}

void display_co_wise_analysis(const AuditReport *report) {
    printf("\n========================================================================================\n");
    printf("          %sMODULE 3: COURSE OUTCOME (CO1 - CO5) DISTRIBUTION ANALYSIS%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");
    printf("| %-8s | %-10s | %-10s | %-10s | %-10s | %-10s |\n",
           "Outcome", "Exp Qs", "Act Qs", "Exp Marks", "Act Marks", "Marks Diff");
    printf("----------------------------------------------------------------------------------------\n");

    for (int co = 1; co <= MAX_COS; co++) {
        const CategoryStat *st = &report->co_stats[co];
        char diff_str[32];
        if (st->marks_diff > 0) {
            snprintf(diff_str, sizeof(diff_str), "%s+%d (Over)%s", COLOR_YELLOW, st->marks_diff, COLOR_RESET);
        } else if (st->marks_diff < 0) {
            snprintf(diff_str, sizeof(diff_str), "%s%d (Under)%s", COLOR_RED, st->marks_diff, COLOR_RESET);
        } else {
            snprintf(diff_str, sizeof(diff_str), "%s0 (Match)%s", COLOR_GREEN, COLOR_RESET);
        }

        printf("| %-8s | %-10d | %-10d | %-10d | %-10d | %-19s |\n",
               st->name, st->expected_questions, st->actual_questions,
               st->expected_marks, st->actual_marks, diff_str);
    }
    printf("========================================================================================\n");
}

void display_cognitive_wise_analysis(const AuditReport *report) {
    printf("\n========================================================================================\n");
    printf("        %sMODULE 3: BLOOM'S COGNITIVE LEVEL DISTRIBUTION ANALYSIS%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");
    printf("| %-18s | %-10s | %-10s | %-10s | %-10s | %-10s |\n",
           "Cognitive Level", "Exp Qs", "Act Qs", "Exp Marks", "Act Marks", "Marks Diff");
    printf("----------------------------------------------------------------------------------------\n");

    for (int lvl = 1; lvl <= 6; lvl++) {
        const CategoryStat *st = &report->cog_stats[lvl];
        char diff_str[32];
        if (st->marks_diff > 0) {
            snprintf(diff_str, sizeof(diff_str), "%s+%d%s", COLOR_YELLOW, st->marks_diff, COLOR_RESET);
        } else if (st->marks_diff < 0) {
            snprintf(diff_str, sizeof(diff_str), "%s%d%s", COLOR_RED, st->marks_diff, COLOR_RESET);
        } else {
            snprintf(diff_str, sizeof(diff_str), "%s0%s", COLOR_GREEN, COLOR_RESET);
        }

        printf("| %-18s | %-10d | %-10d | %-10d | %-10d | %-19s |\n",
               st->name, st->expected_questions, st->actual_questions,
               st->expected_marks, st->actual_marks, diff_str);
    }
    printf("========================================================================================\n");
    printf(" Difficulty Index : %s%.2f / 6.00%s (%s)\n",
           COLOR_BOLD, report->difficulty_index, COLOR_RESET, report->difficulty_rating);
    printf("========================================================================================\n");
}

void display_topic_coverage_analysis(const Blueprint *bp, const QuestionPaper *qp) {
    printf("\n========================================================================================\n");
    printf("                         %sMODULE 3: TOPIC COVERAGE AUDIT%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");
    printf("| %-6s | %-32s | %-15s | %-24s |\n", "Unit", "Prescribed Topic", "Blueprint Marks", "Actual Question Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < bp->rule_count; i++) {
        const BlueprintItem *it = &bp->rules[i];
        int found_count = 0;
        int found_marks = 0;

        for (int j = 0; j < qp->question_count; j++) {
            if (qp->questions[j].unit == it->unit &&
                (strstr(qp->questions[j].topic, it->topic) || strstr(it->topic, qp->questions[j].topic))) {
                found_count++;
                found_marks += qp->questions[j].marks;
            }
        }

        char status[64];
        if (found_count > 0) {
            snprintf(status, sizeof(status), "%sCovered (%d marks)%s", COLOR_GREEN, found_marks, COLOR_RESET);
        } else {
            snprintf(status, sizeof(status), "%sNOT COVERED (Missing!)%s", COLOR_RED, COLOR_RESET);
        }

        printf("| Unit %-1d | %-32.32s | %-15d | %-33s |\n",
               it->unit, it->topic, it->expected_marks, status);
    }
    printf("========================================================================================\n");
}
