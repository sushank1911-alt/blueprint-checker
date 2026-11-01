#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "checker.h"
#include "analysis.h"

int run_blueprint_compliance_check(const Blueprint *bp, const QuestionPaper *qp, AuditReport *report) {
    if (bp->rule_count == 0) {
        printf("%sError: Blueprint is empty! Please load or create a blueprint first.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }
    if (qp->question_count == 0) {
        printf("%sError: Question Paper is empty! Please load or enter questions first.%s\n", COLOR_RED, COLOR_RESET);
        return 0;
    }

    // Step 1: Run Module 3 categorization
    organize_and_analyze_data(bp, qp, report);

    int total_mark_error = 0;
    int total_q_error = 0;

    printf("\n========================================================================================\n");
    printf("            %sMODULE 4: BLUEPRINT COMPLIANCE AUDIT & COMPARISON ENGINE%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");

    // 1. Total Paper Marks Check
    printf("%s[1] Total Marks Verification:%s\n", COLOR_BOLD, COLOR_RESET);
    printf("    Prescribed Blueprint Marks : %d\n", report->total_expected_marks);
    printf("    Actual Question Paper Marks: %d\n", report->total_actual_marks);
    if (report->total_expected_marks != report->total_actual_marks) {
        printf("    --> %sCRITICAL MISMATCH: Net difference of %d marks!%s\n",
               COLOR_RED, report->total_actual_marks - report->total_expected_marks, COLOR_RESET);
        total_mark_error += abs(report->total_actual_marks - report->total_expected_marks);
    } else {
        printf("    --> %sSUCCESS: Total marks match prescribed 70 marks exactly.%s\n", COLOR_GREEN, COLOR_RESET);
    }

    // 2. Unit-wise Marks and Question Discrepancies
    printf("\n%s[2] Unit-wise Distribution Audit:%s\n", COLOR_BOLD, COLOR_RESET);
    for (int u = 0; u < report->num_units; u++) {
        CategoryStat *st = &report->unit_stats[u];
        int m_err = abs(st->marks_diff);
        int q_err = abs(st->question_diff);

        total_mark_error += m_err;
        total_q_error += q_err;

        if (m_err > 0 || q_err > 0) {
            printf("    * %s%s DISCREPANCY:%s Expected %d marks (%d Qs), got %d marks (%d Qs). Diff: %+d marks.\n",
                   COLOR_YELLOW, st->name, COLOR_RESET, st->expected_marks, st->expected_questions,
                   st->actual_marks, st->actual_questions, st->marks_diff);
        } else {
            printf("    * %s%s COMPLIANT:%s %d marks, %d questions (Exact Match).\n",
                   COLOR_GREEN, st->name, COLOR_RESET, st->actual_marks, st->actual_questions);
        }
    }

    // 3. Course Outcome (CO1 - CO5) Distribution Audit
    printf("\n%s[3] Course Outcome (OBE CO1 - CO5) Audit:%s\n", COLOR_BOLD, COLOR_RESET);
    for (int co = 1; co <= MAX_COS; co++) {
        CategoryStat *st = &report->co_stats[co];
        int m_err = abs(st->marks_diff);
        total_mark_error += m_err;

        if (m_err > 0) {
            printf("    * %s%s MISMATCH:%s Expected %d marks, Actual %d marks (Diff: %+d).\n",
                   COLOR_YELLOW, st->name, COLOR_RESET, st->expected_marks, st->actual_marks, st->marks_diff);
        } else if (st->expected_marks > 0) {
            printf("    * %s%s COMPLIANT:%s %d marks allocated (OBE Target Met).\n",
                   COLOR_GREEN, st->name, COLOR_RESET, st->actual_marks);
        }
    }

    // 4. Cognitive Level (Bloom's Taxonomy) Discrepancies
    printf("\n%s[4] Bloom's Cognitive Level Distribution Audit:%s\n", COLOR_BOLD, COLOR_RESET);
    for (int lvl = 1; lvl <= 6; lvl++) {
        CategoryStat *st = &report->cog_stats[lvl];
        int m_err = abs(st->marks_diff);
        total_mark_error += m_err;

        if (m_err > 0) {
            printf("    * %s%s DISCREPANCY:%s Expected %d marks, Actual %d marks (Diff: %+d).\n",
                   COLOR_YELLOW, st->name, COLOR_RESET, st->expected_marks, st->actual_marks, st->marks_diff);
        } else if (st->expected_marks > 0) {
            printf("    * %s%s COMPLIANT:%s %d marks allocated.\n",
                   COLOR_GREEN, st->name, COLOR_RESET, st->actual_marks);
        }
    }

    report->total_mark_discrepancies = total_mark_error;
    report->total_question_discrepancies = total_q_error;

    // Step 3: Compute Compliance Percentage
    float max_penalty = (float)(2 * report->total_expected_marks);
    float score = 100.0f - (((float)total_mark_error / max_penalty) * 100.0f);
    if (score < 0.0f) score = 0.0f;
    report->compliance_percentage = score;

    // Step 4: Assign Verdict
    if (total_mark_error == 0 && total_q_error == 0) {
        strncpy(report->compliance_verdict, "100% COMPLIANT - APPROVED FOR EXAMINATION", MAX_STR - 1);
    } else if (score >= 80.0f) {
        strncpy(report->compliance_verdict, "PARTIALLY COMPLIANT - MINOR CORRECTIONS REQUIRED", MAX_STR - 1);
    } else {
        strncpy(report->compliance_verdict, "NON-COMPLIANT - REJECTED (REVISION REQUIRED)", MAX_STR - 1);
    }

    print_compliance_summary(report);
    return 1;
}

void print_compliance_summary(const AuditReport *report) {
    printf("\n========================================================================================\n");
    printf("                      %sAUDIT VERDICT & FINAL COMPLIANCE SCORE%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");
    printf(" Overall Compliance Score : %s%.2f %%%s\n",
           (report->compliance_percentage >= 90.0f ? COLOR_GREEN : (report->compliance_percentage >= 80.0f ? COLOR_YELLOW : COLOR_RED)),
           report->compliance_percentage, COLOR_RESET);
    printf(" Difficulty Index         : %.2f / 6.00 (%s)\n", report->difficulty_index, report->difficulty_rating);
    printf(" Total Discrepancy Units  : %d mark units\n", report->total_mark_discrepancies);
    printf(" Final Academic Verdict   : %s%s%s\n",
           (report->compliance_percentage >= 90.0f ? COLOR_GREEN : (report->compliance_percentage >= 80.0f ? COLOR_YELLOW : COLOR_RED)),
           report->compliance_verdict, COLOR_RESET);
    printf("========================================================================================\n");
}
