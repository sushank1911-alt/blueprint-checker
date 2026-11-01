#ifndef MODELS_H
#define MODELS_H

#define MAX_RULES 50
#define MAX_QUESTIONS 100
#define MAX_STR 64
#define MAX_TEXT 256
#define MAX_UNITS 10
#define MAX_COS 5

// ANSI Color Codes for enhanced terminal presentation
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_BOLD    "\033[1m"

// Cognitive Levels according to Bloom's Taxonomy
// L1: Remember, L2: Understand, L3: Apply, L4: Analyze, L5: Evaluate, L6: Create
typedef enum {
    COG_NONE = 0,
    COG_L1 = 1, // Remember
    COG_L2 = 2, // Understand
    COG_L3 = 3, // Apply
    COG_L4 = 4, // Analyze
    COG_L5 = 5, // Evaluate
    COG_L6 = 6  // Create
} CognitiveLevel;

// Module 1: Blueprint Rule Item
typedef struct {
    int rule_id;
    int unit;                       // Unit number (1 to 5)
    int co_number;                  // Course Outcome (CO1 to CO5)
    char topic[MAX_STR];            // Topic name
    int cognitive_level;            // Bloom's Level (1 to 6)
    int expected_questions;         // Number of expected questions
    int expected_marks;             // Expected marks
} BlueprintItem;

typedef struct {
    char institution[MAX_STR];
    char department[MAX_STR];
    char subject_name[MAX_STR];
    char exam_name[MAX_STR];
    int total_expected_marks;
    int rule_count;
    BlueprintItem rules[MAX_RULES];
} Blueprint;

// Module 2: Actual Question Item
typedef struct {
    char q_no[16];                  // e.g., "Q1(a)", "Q2"
    char content[MAX_TEXT];         // Question text
    int unit;                       // Unit number
    int co_number;                  // Course Outcome (CO1 to CO5)
    char topic[MAX_STR];            // Topic name
    int cognitive_level;            // 1 to 6
    int marks;                      // Allocated marks
} Question;

typedef struct {
    char institution[MAX_STR];
    char department[MAX_STR];
    char subject_name[MAX_STR];
    char exam_name[MAX_STR];
    int total_marks;
    int question_count;
    Question questions[MAX_QUESTIONS];
} QuestionPaper;

// Module 3: Aggregated Statistics for a Category (Unit, CO, or Cognitive Level)
typedef struct {
    int id;                         // Category ID
    char name[MAX_STR];             // Label (e.g. "Unit 1", "CO 1", "L3: Apply")
    int expected_questions;
    int actual_questions;
    int expected_marks;
    int actual_marks;
    int question_diff;              // actual - expected
    int marks_diff;                 // actual - expected
} CategoryStat;

// Module 4 & 5: Complete Audit Report Structure
typedef struct {
    char subject[MAX_STR];
    char exam[MAX_STR];
    int total_expected_marks;
    int total_actual_marks;
    int total_expected_questions;
    int total_actual_questions;

    // Unit-wise statistics
    int num_units;
    CategoryStat unit_stats[MAX_UNITS];

    // Course Outcome (CO1 to CO5) statistics
    CategoryStat co_stats[MAX_COS + 1]; // indices 1..5

    // Cognitive Level-wise statistics (L1 to L6)
    CategoryStat cog_stats[7];          // indices 1..6

    // Difficulty Index
    float difficulty_index;             // Weighted score 1.0 to 6.0
    char difficulty_rating[MAX_STR];    // Well-Balanced, Easy, Hard

    // Discrepancy & Compliance metrics
    int total_mark_discrepancies;       // Sum of |actual - expected|
    int total_question_discrepancies;
    float compliance_percentage;        // 0.0 to 100.0%
    char compliance_verdict[MAX_STR];   // APPROVED, MINOR DEFECTS, REJECTED
} AuditReport;

// Helpers
const char* get_cognitive_name(int level);
const char* get_cognitive_desc(int level);

#endif // MODELS_H
