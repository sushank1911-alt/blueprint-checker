#include <stdio.h>
#include <string.h>
#include <time.h>
#include "report.h"
#include "analysis.h"

// Helper to convert Cognitive Level int to string
const char* get_cognitive_name(int level) {
    switch (level) {
        case COG_L1: return "L1 (Remember)";
        case COG_L2: return "L2 (Understand)";
        case COG_L3: return "L3 (Apply)";
        case COG_L4: return "L4 (Analyze)";
        case COG_L5: return "L5 (Evaluate)";
        case COG_L6: return "L6 (Create)";
        default: return "Unknown";
    }
}

const char* get_cognitive_desc(int level) {
    switch (level) {
        case COG_L1: return "Recall facts & basic concepts";
        case COG_L2: return "Explain ideas or concepts";
        case COG_L3: return "Use info in new situations";
        case COG_L4: return "Draw connections among ideas";
        case COG_L5: return "Justify a stand or decision";
        case COG_L6: return "Produce new or original work";
        default: return "General";
    }
}

void display_full_compliance_report(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report) {
    printf("\n########################################################################################\n");
    printf("            %sRGM COLLEGE OF ENGINEERING AND TECHNOLOGY (AUTONOMOUS)%s\n", COLOR_CYAN, COLOR_RESET);
    printf("                 DEPARTMENT OF CSE (ARTIFICIAL INTELLIGENCE & ML)\n");
    printf("               OFFICIAL EXAMINATION BLUEPRINT COMPLIANCE AUDIT\n");
    printf("########################################################################################\n");
    printf(" Subject     : %s\n", bp->subject_name);
    printf(" Examination : %s\n", bp->exam_name);
    printf(" Overall Compliance Score : %s%.2f %%%s\n", COLOR_BOLD, report->compliance_percentage, COLOR_RESET);
    printf(" Paper Difficulty Index   : %.2f / 6.00 (%s)\n", report->difficulty_index, report->difficulty_rating);
    printf(" Audit Verdict            : %s\n", report->compliance_verdict);
    printf("----------------------------------------------------------------------------------------\n");

    display_unit_wise_analysis(report);
    display_co_wise_analysis(report);
    display_cognitive_wise_analysis(report);
    display_topic_coverage_analysis(bp, qp);
}

int export_audit_report_to_file(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("%sError: Could not create audit report file '%s'!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    time_t now = time(NULL);
    char date_str[64];
    strftime(date_str, sizeof(date_str), "%d-%b-%Y %H:%M:%S", localtime(&now));

    fprintf(fp, "========================================================================================\n");
    fprintf(fp, "                  RGM COLLEGE OF ENGINEERING AND TECHNOLOGY (AUTONOMOUS)\n");
    fprintf(fp, "                       DEPARTMENT OF CSE (ARTIFICIAL INTELLIGENCE & ML)\n");
    fprintf(fp, "                     OFFICIAL EXAMINATION BLUEPRINT COMPLIANCE REPORT\n");
    fprintf(fp, "========================================================================================\n");
    fprintf(fp, " Report Generated On : %s\n", date_str);
    fprintf(fp, " Institution         : %s\n", bp->institution);
    fprintf(fp, " Department          : %s\n", bp->department);
    fprintf(fp, " Subject             : %s\n", bp->subject_name);
    fprintf(fp, " Examination         : %s\n", bp->exam_name);
    fprintf(fp, "----------------------------------------------------------------------------------------\n");
    fprintf(fp, " EXECUTIVE SUMMARY:\n");
    fprintf(fp, "   * Total Blueprint Marks Expected : %d\n", report->total_expected_marks);
    fprintf(fp, "   * Total Question Paper Marks Got : %d\n", report->total_actual_marks);
    fprintf(fp, "   * Compliance Percentage          : %.2f %%\n", report->compliance_percentage);
    fprintf(fp, "   * Paper Difficulty Index         : %.2f / 6.00 (%s)\n", report->difficulty_index, report->difficulty_rating);
    fprintf(fp, "   * Audit Decision Status          : %s\n", report->compliance_verdict);
    fprintf(fp, "========================================================================================\n\n");

    // 1. Unit Analysis
    fprintf(fp, "SECTION 1: UNIT-WISE MARKS AND QUESTION DISTRIBUTION\n");
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n");
    fprintf(fp, "| Unit     | Exp Qs     | Act Qs     | Exp Marks  | Act Marks  | Status / Difference   |\n");
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n");
    for (int u = 0; u < report->num_units; u++) {
        const CategoryStat *st = &report->unit_stats[u];
        char diff_str[32];
        if (st->marks_diff > 0) snprintf(diff_str, sizeof(diff_str), "+%d Marks (Over)", st->marks_diff);
        else if (st->marks_diff < 0) snprintf(diff_str, sizeof(diff_str), "%d Marks (Under)", st->marks_diff);
        else snprintf(diff_str, sizeof(diff_str), "COMPLIANT (Exact)");

        fprintf(fp, "| %-8s | %-10d | %-10d | %-10d | %-10d | %-21s |\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, diff_str);
    }
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n\n");

    // 2. Course Outcomes Analysis
    fprintf(fp, "SECTION 2: COURSE OUTCOME (OBE CO1 - CO5) DISTRIBUTION\n");
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n");
    fprintf(fp, "| Outcome  | Exp Qs     | Act Qs     | Exp Marks  | Act Marks  | Status / Difference   |\n");
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n");
    for (int co = 1; co <= MAX_COS; co++) {
        const CategoryStat *st = &report->co_stats[co];
        char diff_str[32];
        if (st->marks_diff > 0) snprintf(diff_str, sizeof(diff_str), "+%d Marks (Over)", st->marks_diff);
        else if (st->marks_diff < 0) snprintf(diff_str, sizeof(diff_str), "%d Marks (Under)", st->marks_diff);
        else snprintf(diff_str, sizeof(diff_str), "COMPLIANT (Exact)");

        fprintf(fp, "| %-8s | %-10d | %-10d | %-10d | %-10d | %-21s |\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, diff_str);
    }
    fprintf(fp, "+----------+------------+------------+------------+------------+-----------------------+\n\n");

    // 3. Cognitive Analysis
    fprintf(fp, "SECTION 3: BLOOM'S TAXONOMY COGNITIVE LEVEL DISTRIBUTION\n");
    fprintf(fp, "+--------------------+------------+------------+------------+------------+-------------+\n");
    fprintf(fp, "| Cognitive Level    | Exp Qs     | Act Qs     | Exp Marks  | Act Marks  | Difference  |\n");
    fprintf(fp, "+--------------------+------------+------------+------------+------------+-------------+\n");
    for (int lvl = 1; lvl <= 6; lvl++) {
        const CategoryStat *st = &report->cog_stats[lvl];
        fprintf(fp, "| %-18s | %-10d | %-10d | %-10d | %-10d | %+11d |\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, st->marks_diff);
    }
    fprintf(fp, "+--------------------+------------+------------+------------+------------+-------------+\n\n");

    // 4. Questions Inventory
    fprintf(fp, "SECTION 4: DETAILED QUESTION INVENTORY (WITH CO MAPPING)\n");
    fprintf(fp, "+--------+--------+--------+----------------------------------------------------+---------------+-------+\n");
    fprintf(fp, "| Q.No   | Unit   | CO     | Question Statement                                 | Bloom's Level | Marks |\n");
    fprintf(fp, "+--------+--------+--------+----------------------------------------------------+---------------+-------+\n");
    for (int i = 0; i < qp->question_count; i++) {
        const Question *q = &qp->questions[i];
        fprintf(fp, "| %-6s | Unit %-1d | CO %-2d | %-50.50s | %-13s | %-5d |\n",
                q->q_no, q->unit, q->co_number, q->content, get_cognitive_name(q->cognitive_level), q->marks);
    }
    fprintf(fp, "+--------+--------+--------+----------------------------------------------------+---------------+-------+\n\n");

    fprintf(fp, "========================================================================================\n");
    fprintf(fp, " PROJECT TEAM & VERIFICATION SIGNATURES:\n");
    fprintf(fp, "   * Project Supervisor : Dr. G. Chakrapani (Assistant Professor, CSE AI&ML)\n");
    fprintf(fp, "   * Student Team       : K. Sushank (25091A33M7), Y. V. Jaswanth Reddy (25091A33P6),\n");
    fprintf(fp, "                          S. Jafar Hussain Ali (24091A3359)\n\n\n");
    fprintf(fp, " _________________________                     _________________________\n");
    fprintf(fp, " Dr. G. Chakrapani                             Dr. G. Kishore Kumar\n");
    fprintf(fp, " Project Supervisor                            Professor & HOD, CSE (AI&ML)\n");
    fprintf(fp, "========================================================================================\n");

    fclose(fp);
    printf("%sAudit Report successfully exported to file: '%s'%s\n", COLOR_GREEN, filename, COLOR_RESET);
    return 1;
}

// Export clean CSV report for Microsoft Excel
int export_audit_report_to_csv(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("%sError: Could not create CSV report '%s'!%s\n", COLOR_RED, filename, COLOR_RESET);
        return 0;
    }

    fprintf(fp, "Examination Blueprint Validation Audit Report\n");
    fprintf(fp, "Institution,%s\n", bp->institution);
    fprintf(fp, "Department,%s\n", bp->department);
    fprintf(fp, "Subject,%s\n", bp->subject_name);
    fprintf(fp, "Examination,%s\n", bp->exam_name);
    fprintf(fp, "Compliance Score,%.2f %%\n", report->compliance_percentage);
    fprintf(fp, "Difficulty Index,%.2f / 6.00 (%s)\n", report->difficulty_index, report->difficulty_rating);
    fprintf(fp, "Audit Verdict,%s\n\n", report->compliance_verdict);

    // Unit table
    fprintf(fp, "Unit-wise Distribution Analysis\n");
    fprintf(fp, "Unit,Expected Questions,Actual Questions,Expected Marks,Actual Marks,Difference\n");
    for (int u = 0; u < report->num_units; u++) {
        const CategoryStat *st = &report->unit_stats[u];
        fprintf(fp, "%s,%d,%d,%d,%d,%d\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, st->marks_diff);
    }
    fprintf(fp, "\n");

    // CO table
    fprintf(fp, "Course Outcome (CO) Distribution Analysis\n");
    fprintf(fp, "Outcome,Expected Questions,Actual Questions,Expected Marks,Actual Marks,Difference\n");
    for (int co = 1; co <= MAX_COS; co++) {
        const CategoryStat *st = &report->co_stats[co];
        fprintf(fp, "%s,%d,%d,%d,%d,%d\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, st->marks_diff);
    }
    fprintf(fp, "\n");

    // Bloom table
    fprintf(fp, "Bloom's Cognitive Level Analysis\n");
    fprintf(fp, "Cognitive Level,Expected Questions,Actual Questions,Expected Marks,Actual Marks,Difference\n");
    for (int lvl = 1; lvl <= 6; lvl++) {
        const CategoryStat *st = &report->cog_stats[lvl];
        fprintf(fp, "%s,%d,%d,%d,%d,%d\n",
                st->name, st->expected_questions, st->actual_questions,
                st->expected_marks, st->actual_marks, st->marks_diff);
    }
    fprintf(fp, "\n");

    // Question Inventory
    fprintf(fp, "Question Inventory\n");
    fprintf(fp, "Question No,Unit,Course Outcome,Question Statement,Cognitive Level,Marks\n");
    for (int i = 0; i < qp->question_count; i++) {
        const Question *q = &qp->questions[i];
        fprintf(fp, "\"%s\",Unit %d,CO %d,\"%s\",\"%s\",%d\n",
                q->q_no, q->unit, q->co_number, q->content, get_cognitive_name(q->cognitive_level), q->marks);
    }

    fclose(fp);
    printf("%sExcel CSV Audit Report exported to: '%s'%s\n", COLOR_GREEN, filename, COLOR_RESET);
    return 1;
}
