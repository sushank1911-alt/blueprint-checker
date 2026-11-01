#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "blueprint.h"
#include "question_paper.h"
#include "analysis.h"
#include "checker.h"
#include "report.h"
#include "ai_helper.h"

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Submenu for Module 1
static void menu_blueprint(Blueprint *bp) {
    int choice;
    while (1) {
        printf("\n--- [%sMODULE 1: BLUEPRINT MANAGEMENT%s] ---\n", COLOR_CYAN, COLOR_RESET);
        printf("1. View Current Blueprint (Units, COs, Bloom's Levels)\n");
        printf("2. Add New Blueprint Rule\n");
        printf("3. Modify a Rule\n");
        printf("4. Delete a Rule\n");
        printf("5. Save Blueprint to File\n");
        printf("6. Load Blueprint from File\n");
        printf("7. Load Standard RGM Autonomous 70-Marks Blueprint (5 Units & 5 COs)\n");
        printf("8. Return to Main Menu\n");
        printf("Enter choice (1-8): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                view_blueprint(bp);
                break;
            case 2: {
                int unit, co, cog, exp_q, exp_m;
                char topic[MAX_STR];
                printf("Enter Unit Number (1-5): ");
                scanf("%d", &unit);
                printf("Enter Course Outcome CO (1-5): ");
                scanf("%d", &co);
                clear_input_buffer();
                printf("Enter Topic Name: ");
                if (fgets(topic, sizeof(topic), stdin)) {
                    topic[strcspn(topic, "\r\n")] = '\0';
                }
                printf("Enter Cognitive Level (1:L1 .. 6:L6): ");
                scanf("%d", &cog);
                printf("Enter Expected Questions: ");
                scanf("%d", &exp_q);
                printf("Enter Expected Marks: ");
                scanf("%d", &exp_m);
                add_blueprint_rule(bp, unit, co, topic, cog, exp_q, exp_m);
                printf("%sRule added successfully! Current Blueprint Total: %d Marks.%s\n",
                       COLOR_GREEN, bp->total_expected_marks, COLOR_RESET);
                break;
            }
            case 3: {
                int id;
                printf("Enter Rule ID to modify: ");
                scanf("%d", &id);
                modify_blueprint_rule(bp, id);
                break;
            }
            case 4: {
                int id;
                printf("Enter Rule ID to delete: ");
                scanf("%d", &id);
                delete_blueprint_rule(bp, id);
                break;
            }
            case 5: {
                char fname[64];
                printf("Enter filename (default: blueprint.txt): ");
                scanf("%63s", fname);
                save_blueprint_to_file(bp, fname);
                break;
            }
            case 6: {
                char fname[64];
                printf("Enter filename to load (default: blueprint.txt): ");
                scanf("%63s", fname);
                load_blueprint_from_file(bp, fname);
                break;
            }
            case 7:
                load_default_rgm_blueprint(bp);
                break;
            case 8:
                return;
            default:
                printf("%sInvalid choice!%s\n", COLOR_RED, COLOR_RESET);
        }
    }
}

// Submenu for Module 2
static void menu_question_paper(QuestionPaper *qp) {
    int choice;
    while (1) {
        printf("\n--- [%sMODULE 2: QUESTION PAPER MANAGEMENT%s] ---\n", COLOR_CYAN, COLOR_RESET);
        printf("1. View Current Question Paper Inventory\n");
        printf("2. Add New Question (with AI Bloom's Taxonomy Assistant)\n");
        printf("3. Modify a Question\n");
        printf("4. Delete a Question\n");
        printf("5. Save Question Paper to File\n");
        printf("6. Load Question Paper from File\n");
        printf("7. Return to Main Menu\n");
        printf("Enter choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                view_question_paper(qp);
                break;
            case 2: {
                char q_no[16], content[MAX_TEXT], topic[MAX_STR];
                int unit, co, cog, marks;

                printf("Enter Question No (e.g., Q1a, Q2): ");
                scanf("%15s", q_no);
                clear_input_buffer();

                printf("Enter Question Content: ");
                if (fgets(content, sizeof(content), stdin)) {
                    content[strcspn(content, "\r\n")] = '\0';
                }

                int ai_suggested = ai_predict_cognitive_level(content);
                if (ai_suggested != COG_NONE) {
                    printf(">> %s[AI Recommendation]%s Action verb suggests: %s (%s)\n",
                           COLOR_CYAN, COLOR_RESET,
                           get_cognitive_name(ai_suggested), get_cognitive_desc(ai_suggested));
                }

                printf("Enter Unit (1-5): ");
                scanf("%d", &unit);

                printf("Enter Course Outcome CO (1-5): ");
                scanf("%d", &co);
                clear_input_buffer();

                printf("Enter Topic Name: ");
                if (fgets(topic, sizeof(topic), stdin)) {
                    topic[strcspn(topic, "\r\n")] = '\0';
                }

                printf("Enter Cognitive Level (1:L1 .. 6:L6): ");
                scanf("%d", &cog);

                printf("Enter Marks: ");
                scanf("%d", &marks);

                add_question(qp, q_no, content, unit, co, topic, cog, marks);
                printf("%sQuestion added! Current Paper Marks: %d.%s\n", COLOR_GREEN, qp->total_marks, COLOR_RESET);
                break;
            }
            case 3: {
                int idx;
                printf("Enter Question Index (1 to %d): ", qp->question_count);
                scanf("%d", &idx);
                modify_question(qp, idx);
                break;
            }
            case 4: {
                int idx;
                printf("Enter Question Index (1 to %d) to delete: ", qp->question_count);
                scanf("%d", &idx);
                delete_question(qp, idx);
                break;
            }
            case 5: {
                char fname[64];
                printf("Enter filename (default: question_paper.txt): ");
                scanf("%63s", fname);
                save_question_paper_to_file(qp, fname);
                break;
            }
            case 6: {
                char fname[64];
                printf("Enter filename to load (default: question_paper.txt): ");
                scanf("%63s", fname);
                load_question_paper_from_file(qp, fname);
                break;
            }
            case 7:
                return;
            default:
                printf("%sInvalid choice!%s\n", COLOR_RED, COLOR_RESET);
        }
    }
}

// Submenu for Module 3
static void menu_analysis(const Blueprint *bp, const QuestionPaper *qp, AuditReport *report) {
    if (bp->rule_count == 0 || qp->question_count == 0) {
        printf("%sError: Please make sure both Blueprint and Question Paper are loaded!%s\n", COLOR_RED, COLOR_RESET);
        return;
    }

    organize_and_analyze_data(bp, qp, report);
    int choice;
    while (1) {
        printf("\n--- [%sMODULE 3: DATA ORGANIZATION & MULTI-DIMENSIONAL ANALYSIS%s] ---\n", COLOR_CYAN, COLOR_RESET);
        printf("1. View Unit-wise Distribution & Differences\n");
        printf("2. View Course Outcome (OBE CO1 - CO5) Distribution\n");
        printf("3. View Cognitive Level (Bloom's Taxonomy) Distribution & Difficulty Index\n");
        printf("4. View Topic Coverage Audit\n");
        printf("5. Return to Main Menu\n");
        printf("Enter choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                display_unit_wise_analysis(report);
                break;
            case 2:
                display_co_wise_analysis(report);
                break;
            case 3:
                display_cognitive_wise_analysis(report);
                break;
            case 4:
                display_topic_coverage_analysis(bp, qp);
                break;
            case 5:
                return;
            default:
                printf("%sInvalid choice!%s\n", COLOR_RED, COLOR_RESET);
        }
    }
}

int main(void) {
    Blueprint bp;
    QuestionPaper qp;
    AuditReport report;

    init_blueprint(&bp);
    init_question_paper(&qp);
    memset(&report, 0, sizeof(AuditReport));

    // Preload default RGM Autonomous sample 70-marks paper & blueprint
    load_default_rgm_blueprint(&bp);
    load_default_rgm_question_paper(&qp, 0);

    int main_choice;

    while (1) {
        printf("\n========================================================================================\n");
        printf("         %sRGM COLLEGE OF ENGINEERING AND TECHNOLOGY (AUTONOMOUS), NANDYAL%s\n", COLOR_BOLD, COLOR_RESET);
        printf("                     DEPARTMENT OF CSE (AI&ML) - AY 2026-27\n");
        printf("           %sEXAMINATION QUESTION PAPER BLUEPRINT CHECKER & VALIDATION SYSTEM%s\n", COLOR_CYAN, COLOR_RESET);
        printf("========================================================================================\n");
        printf(" [Active State] Blueprint: %d Rules (%d Marks) | Questions: %d Qs (%d Marks)\n",
               bp.rule_count, bp.total_expected_marks, qp.question_count, qp.total_marks);
        printf("----------------------------------------------------------------------------------------\n");
        printf(" 1. Module 1: Blueprint Management (Add, View, Modify, Save/Load)\n");
        printf(" 2. Module 2: Question Paper Management (Enter, View, Save/Load)\n");
        printf(" 3. Module 3: Data Organization & Analysis (Unit, CO1-CO5, Bloom's, Topic)\n");
        printf(" 4. Module 4: Run Blueprint Checking & Comparison Engine\n");
        printf(" 5. Module 5: View Compliance Report & Export Files (.txt & .csv)\n");
        printf(" 6. %sAI Feature%s: Question Similarity & Redundancy Detector (Jaccard Similarity)\n", COLOR_MAGENTA, COLOR_RESET);
        printf(" 7. [Testing] Load Test Scenario 1: Compliant Paper (100%% Score, CO1-CO5)\n");
        printf(" 8. [Testing] Load Test Scenario 2: Flawed Paper with Violations (< 80%% Score)\n");
        printf(" 9. Exit System\n");
        printf("========================================================================================\n");
        printf(" Select Option (1-9): ");

        if (scanf("%d", &main_choice) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (main_choice) {
            case 1:
                menu_blueprint(&bp);
                break;
            case 2:
                menu_question_paper(&qp);
                break;
            case 3:
                menu_analysis(&bp, &qp, &report);
                break;
            case 4:
                run_blueprint_compliance_check(&bp, &qp, &report);
                break;
            case 5:
                if (report.total_expected_marks == 0) {
                    run_blueprint_compliance_check(&bp, &qp, &report);
                }
                display_full_compliance_report(&bp, &qp, &report);
                printf("\nExport audit report options:\n");
                printf("  1. Export Printable Text Document ('audit_report.txt')\n");
                printf("  2. Export Excel Spreadsheet ('audit_report.csv')\n");
                printf("  3. Export Both\n");
                printf("  4. Cancel\n");
                printf("Select option (1-4): ");
                int exp;
                if (scanf("%d", &exp) == 1) {
                    if (exp == 1 || exp == 3) {
                        export_audit_report_to_file(&bp, &qp, &report, "audit_report.txt");
                    }
                    if (exp == 2 || exp == 3) {
                        export_audit_report_to_csv(&bp, &qp, &report, "audit_report.csv");
                    }
                }
                break;
            case 6:
                ai_check_question_similarity(&qp, 0.35f);
                break;
            case 7:
                load_default_rgm_blueprint(&bp);
                load_default_rgm_question_paper(&qp, 0);
                run_blueprint_compliance_check(&bp, &qp, &report);
                break;
            case 8:
                load_default_rgm_blueprint(&bp);
                load_default_rgm_question_paper(&qp, 1);
                run_blueprint_compliance_check(&bp, &qp, &report);
                break;
            case 9:
                printf("\nThank you for using the Blueprint Checker System. Exiting.\n");
                return 0;
            default:
                printf("%sInvalid selection! Please enter a number between 1 and 9.%s\n", COLOR_RED, COLOR_RESET);
        }
    }

    return 0;
}
