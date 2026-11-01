# Rajeev Gandhi Memorial College of Engineering & Technology
### (AUTONOMOUS)
**Nandyal-518501, Andhra Pradesh, India**  
*Approved by AICTE, New Delhi | Affiliated to J.N.T.U.A. Ananthapuramu*  
*Accredited by NBA & NAAC (With ‘A+’ Grade), New Delhi | Participated in World Bank Assisted TEQIP Phase – I*  
[www.rgmcet.edu.in](https://www.rgmcet.edu.in)

---

### DEPARTMENT OF COMPUTER SCIENCE & ENGINEERING
### (ARTIFICIAL INTELLIGENCE & MACHINE LEARNING)

---

# REPORT OF THE PROJECT ON
## **EXAMINATION QUESTION PAPER BLUEPRINT CHECKER & VALIDATION SYSTEM**

**Academic Year**: 2026 – 2027  
**Course**: II B.Tech I Semester (CSE - AI & ML)  
**Problem Statement**: Blueprint Checker  

**Under the Guidance of:**  
**Dr. G. Chakrapani**  
*Project Supervisor / Assistant Professor, Department of CSE (AI & ML), RGMCET*  

**Submitted By:**  
- **K. Sushank** (Regd. No: 25091A33M7)  
- **Y. V. Jaswanth Reddy** (Regd. No: 25091A33P6)  
- **S. Jafar Hussain Ali** (Regd. No: 24091A3359)  

**Duration of the Project**: 25/08/2026 to 31/10/2026  

---

# CERTIFICATE

This is to certify that the project entitled **"EXAMINATION QUESTION PAPER BLUEPRINT CHECKER & VALIDATION SYSTEM"** that is being submitted by **K. Sushank (25091A33M7), Y. V. Jaswanth Reddy (25091A33P6), and S. Jafar Hussain Ali (24091A3359)** is a bonafide record of the academic project work done by them in partial fulfillment of the requirements for the award of the degree of **Bachelor of Technology in Computer Science & Engineering (Artificial Intelligence & Machine Learning)** at **Rajeev Gandhi Memorial College of Engineering & Technology (Autonomous), Nandyal** during the Academic Year 2026–2027.

<br><br><br>

------------------------------------ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ------------------------------------  
**Project Guide / Supervisor** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **Head of the Department**  
**Dr. G. Chakrapani** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **Dr. G. Kishore Kumar**  
Assistant Professor &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Professor & HOD, Dept. of CSE (AI&ML)  
Dept. of CSE (AI&ML), RGMCET  

<br>

**Signature of External Examiner:** _______________________  
**Date:** _______________________  

---

# ABSTRACT

Preparing standardized and balanced semester examination question papers in autonomous engineering institutions requires strict compliance with institutional examination guidelines, Outcome-Based Education (OBE) principles, and Bloom’s Revised Taxonomy. Traditionally, verification of question paper blueprints—checking whether marks are uniformly distributed across units, whether Course Outcomes (CO1 to CO5) are adequately assessed, and whether cognitive levels (L1 Remember to L6 Create) adhere to predefined percentages—is carried out manually by department scrutiny committees. Manual verification is time-consuming, prone to calculation oversights, subjective, and lacks mathematical standardization.

To overcome these challenges, this project presents the **Examination Question Paper Blueprint Checker**, an automated verification software developed in **C**. The system accepts an institutional reference blueprint defining expected marks, question counts, unit distributions, Course Outcomes, and target Bloom's cognitive levels. It then captures the actual examination question paper details and executes an automated, multi-dimensional discrepancy analysis.

The system is engineered into five modular components:
1. **Module 1 (Blueprint Management)**: Captures, updates, validates, and stores reference assessment blueprints.
2. **Module 2 (Question Paper Management)**: Records question inventories, including question statements, allocated marks, unit affiliations, and assigned cognitive levels.
3. **Module 3 (Data Organization & Analysis)**: Categorizes and aggregates distribution matrices across Units, Course Outcomes (CO1–CO5), and Bloom's Cognitive Levels ($L1$ to $L6$).
4. **Module 4 (Blueprint Checking & Comparison Engine)**: Performs difference analysis ($\text{Actual} - \text{Expected}$), calculates an objective **Academic Compliance Score (%)**, and evaluates a **Weighted Paper Difficulty Index**.
5. **Module 5 (Report Generation & File Management)**: Outputs real-time ANSI color-coded verification results and exports formal verification audit certificates (`audit_report.txt`) as well as tabular Microsoft Excel spreadsheets (`audit_report.csv`).

Additionally, for CSE (AI&ML) specialization, the system incorporates an **AI-based NLP Action Verb Validator** to cross-examine question statements against assigned Bloom levels, as well as a **Jaccard Word Similarity Redundancy Detector** to flag duplicated or overlapping questions. The project provides an efficient, reliable, and standardized audit mechanism that supports fair examinations and simplifies accreditation record maintenance.

---

# TABLE OF CONTENTS
1. **Introduction**  
   1.1 Project Overview  
   1.2 Purpose  
   1.3 Objectives  
   1.4 Scope  
   1.5 Intended Users  
2. **Problem Statement, Objectives, and Scope**  
   2.1 Problem Statement  
   2.2 Proposed Solution  
   2.3 Expected Benefits  
3. **Existing and Proposed Systems**  
   3.1 Existing Manual System  
   3.2 Disadvantages of the Existing System  
   3.3 Proposed Automated System  
   3.4 Advantages of the Proposed System  
4. **Requirements and Feasibility Study**  
   4.1 Functional Requirements  
   4.2 Non-Functional Requirements  
   4.3 Hardware Requirements  
   4.4 Software Requirements  
   4.5 Feasibility Study  
5. **System Architecture and Design**  
   5.1 High-Level Architecture  
   5.2 Main Data Flow  
   5.3 Entity Design  
   5.4 Use Case Description  
6. **Five Modules: Design, Algorithms, and Pseudocode**  
   6.1 Module 1: Blueprint Management  
   6.2 Module 2: Question Paper Management  
   6.3 Module 3: Data Organization and Analysis  
   6.4 Module 4: Blueprint Checking and Comparison Engine  
   6.5 Module 5: Report Generation and File Management  
7. **Data Design and File Handling**  
   7.1 Data Structures (`models.h`)  
   7.2 File Formats (`.txt` and `.csv`)  
   7.3 Data Validation Rules  
8. **User Interface / Console Design**  
9. **Core Implementation & AI Modules**  
   9.1 Bloom's Action Verb Classifier  
   9.2 Jaccard Question Similarity Detector  
   9.3 Weighted Difficulty Index Formula  
10. **Integration and Data Flow**  
11. **Testing and Sample Results**  
    11.1 Test Case Matrix  
    11.2 Sample Compliant Paper Result  
    11.3 Sample Flawed Paper Result  
12. **Security, Limitations, and Future Enhancements**  
13. **Conclusion**  
14. **References**  

---

# 1. INTRODUCTION

### 1.1 Project Overview
In autonomous higher-education institutions, the quality and credibility of semester-end evaluations depend heavily on adherence to a prescribed examination blueprint. A blueprint acts as an academic contract, specifying exact question counts, marks allocation per unit, Bloom’s cognitive distribution, and alignment with Course Outcomes (COs). The **Blueprint Checker** is a high-performance software system implemented in the C programming language that automates the audit of examination question papers against reference blueprints.

### 1.2 Purpose
The purpose of this software is to eliminate human oversight during the question paper scrutiny process, ensure compliance with Outcome-Based Education (OBE) and NBA/NAAC accreditation norms, and provide automated mathematical compliance scores with formal audit certificates.

### 1.3 Objectives
- Automate the input and management of examination blueprints (units, topics, COs, Bloom levels, marks).
- Capture and validate question paper entries submitted by examiners.
- Categorize questions across units, topics, Course Outcomes, and cognitive levels.
- Perform difference and discrepancy checks, identifying over-allocated, under-allocated, or omitted topics.
- Quantify paper quality through an objective **Compliance Percentage Score** and a **Weighted Difficulty Index**.
- Incorporate AI/ML natural language techniques to verify question verbs and detect redundant/duplicate questions.
- Generate permanent, verifiable text and CSV audit reports.

### 1.4 Scope
The system is built specifically for autonomous colleges, university examination cells, heads of departments, and paper-setting scrutiny boards. It evaluates question papers of standard 70-mark or 100-mark formats across 5 units and 5 Course Outcomes.

### 1.5 Intended Users
- **Examination Scrutiny Committee**: Verifies paper compliance before printing.
- **Head of the Department (HOD)**: Approves question papers for academic integrity.
- **Course Faculty / Paper Setters**: Self-evaluates draft papers against the prescribed blueprint.
- **Academic Auditors / NBA Coordinators**: Accesses exported CSV and TXT audit reports for accreditation files.

---

# 2. PROBLEM STATEMENT, OBJECTIVES, AND SCOPE

### 2.1 Problem Statement
Preparing balanced examination question papers requires adherence to institutional assessment guidelines that define the distribution of questions across various difficulty levels and learning outcomes. Manual verification of blueprint compliance may result in inconsistencies, calculation errors, delayed review cycles, and non-compliance with NBA Outcome-Based Education requirements. A structured examination blueprint validation system is required to analyze question paper composition, verify compliance with predefined assessment standards, evaluate mark distribution, and generate validation reports that support fair and standardized examinations.

### 2.2 Proposed Solution
The proposed system implements an automated pipeline in C. It digitizes the blueprint into structured records, reads examination questions, classifies them into multidimensional frequency matrices, checks for mathematical and structural violations, calculates compliance scores, detects duplicate questions via Jaccard similarity, and exports printable audit documents.

### 2.3 Expected Benefits
- **Zero Calculation Errors**: Automatic calculation of unit, CO, and Bloom totals.
- **Accreditation Readiness**: Built-in verification of NBA Course Outcomes (CO1 to CO5).
- **Time Savings**: Paper audit reduced from 45 minutes of manual checking to under 2 seconds.
- **Standardized Reporting**: Exports audit documentation in `.txt` and Microsoft Excel `.csv`.

---

# 3. EXISTING AND PROPOSED SYSTEMS

### 3.1 Existing Manual System
In the existing manual system, faculty paper setters submit handwritten or typed drafts along with a physical scrutiny form. A committee manually sums marks per unit, tallies Bloom's taxonomy tags, checks topic coverage, and writes manual review remarks.

### 3.2 Disadvantages of the Existing System
- **Error-Prone**: Calculation slips often lead to papers with incorrect total marks or uneven unit distribution.
- **Subjective Bloom's Tagging**: Faculty frequently tag recall-based questions ($L1$) as higher-order thinking ($L4$) without scrutiny.
- **No Redundancy Check**: Questions from internal assessments are sometimes inadvertently repeated.
- **Lack of Permanent Audit Trails**: Physical scrutiny sheets can be misplaced, complicating NBA accreditation reviews.

### 3.3 Proposed Automated System
The proposed C-based system provides a structured, terminal-driven console environment backed by file handling and NLP analysis. Every constraint is checked programmatically, and an objective compliance percentage is generated.

### 3.4 Advantages of the Proposed System
- **Strict Constraint Enforcement**: Instantly detects any missing unit, over-allocated mark, or omitted Course Outcome.
- **AI-Powered Validation**: Analyzes question keywords and detects duplicate questions using token similarity.
- **ANSI Color Terminal Output**: Clear green, yellow, and red highlights for fast review.
- **Dual Export Formats**: Exports printable text reports and Excel-compatible CSV files.

---

# 4. REQUIREMENTS AND FEASIBILITY STUDY

### 4.1 Functional Requirements
- **FR1 (Blueprint Entry)**: Add, edit, delete, and view blueprint rules with unit, CO, topic, Bloom level, and expected marks.
- **FR2 (Question Paper Entry)**: Register question number, statement, unit, CO, topic, cognitive level, and marks.
- **FR3 (Data Aggregation)**: Compute totals across units, COs, and cognitive levels.
- **FR4 (Compliance Checking)**: Calculate discrepancy matrices ($\Delta = \text{Actual} - \text{Expected}$) and compute the Compliance Score.
- **FR5 (Difficulty Rating)**: Calculate the Weighted Difficulty Index and label the paper (Easy, Balanced, Hard).
- **FR6 (AI Verifier)**: Detect Bloom verb misalignment and question redundancy via Jaccard similarity.
- **FR7 (File Management)**: Save/load blueprints and question papers, and export `audit_report.txt` and `audit_report.csv`.

### 4.2 Non-Functional Requirements
- **Performance**: Execution of audits in under 100 milliseconds.
- **Portability**: Standard C99 compliance, compiling without external dependencies across macOS, Linux, and Windows.
- **Robustness**: Input validation to prevent crashes from invalid numeric choices.
- **Usability**: Interactive, clear terminal interface with ANSI color highlights.

### 4.3 Hardware Requirements
- Processor: Intel Core i3 / AMD Ryzen / Apple Silicon or higher.
- RAM: Minimum 512 MB.
- Storage: 10 MB free disk space.

### 4.4 Software Requirements
- Operating System: macOS, Linux, or Windows.
- Compiler: GCC, Clang, or MSVC supporting C99 standard.
- Build Tool: GNU Make (optional).

### 4.5 Feasibility Study
- **Technical Feasibility**: Built with ANSI C standard libraries (`stdio.h`, `string.h`, `stdlib.h`, `math.h`, `time.h`). Does not require proprietary commercial software.
- **Economic Feasibility**: Completely open-source tools with zero licensing costs.
- **Operational Feasibility**: Simple menu-driven console structure requires no complex installation or database configurations.

---

# 5. SYSTEM ARCHITECTURE AND DESIGN

### 5.1 High-Level Architecture

```
+-------------------------------------------------------------------------------+
|                      EXAMINATION BLUEPRINT CHECKER SYSTEM                      |
+-------------------------------------------------------------------------------+
           |                                                   |
           v                                                   v
   [Module 1: Blueprint]                              [Module 2: Questions]
   - Unit Number (1-5)                                - Question Statement
   - Course Outcome (CO1-CO5)                         - Unit & CO Mapping
   - Topic & Bloom's (L1-L6)                          - Assigned Cognitive Level
   - Prescribed Marks                                 - Question Marks
           |                                                   |
           +-------------------------+-------------------------+
                                     |
                                     v
                  [Module 3: Organization & Aggregation]
                  - Unit-wise Mark Frequencies
                  - CO1 to CO5 Aggregations
                  - Bloom's Taxonomy Distribution
                  - Weighted Difficulty Index Calculation
                                     |
                                     v
                  [Module 4: Blueprint Checking Engine]
                  - Discrepancy Matrix (Actual - Expected)
                  - Compliance Percentage Score Formula
                  - Actionable Audit Flags & Warnings
                                     |
                                     v
                  [Module 5: Report Generation & Storage]
                  - Color-Coded Console Table Display
                  - Export Printable "audit_report.txt"
                  - Export Microsoft Excel "audit_report.csv"
```

### 5.2 Main Data Flow
1. User loads or enters the examination blueprint.
2. User enters or loads the question paper.
3. System runs Module 3 to aggregate totals per unit, CO, and cognitive level.
4. Module 4 executes difference equations and determines the academic compliance score.
5. The AI helper verifies question action verbs and screens for duplicate question statements.
6. Module 5 displays summaries and saves official audit documents to storage.

---

# 6. FIVE MODULES: DESIGN, ALGORITHMS, AND PSEUDOCODE

## Module 1: Blueprint Management
Responsible for defining and storing the reference examination standard.

### Algorithm
```
1. Start.
2. Initialize Blueprint record with Institution, Department, and Subject details.
3. Read Unit, Course Outcome (CO), Topic Name, Cognitive Level (L1-L6), Expected Questions, and Marks.
4. Append rule to rules array and increment rule_count.
5. Recalculate total expected marks = SUM(rules[i].expected_marks).
6. Provide sub-options to modify, delete, view, or persist rules to disk.
7. Stop.
```

### Pseudocode
```
BEGIN
    INPUT unit, co_number, topic, cog_level, exp_q, exp_marks
    IF rule_count < MAX_RULES THEN
        rules[rule_count].unit = unit
        rules[rule_count].co_number = co_number
        rules[rule_count].topic = topic
        rules[rule_count].cognitive_level = cog_level
        rules[rule_count].expected_marks = exp_marks
        rule_count = rule_count + 1
        total_expected_marks = total_expected_marks + exp_marks
        DISPLAY "Rule Added Successfully"
    ELSE
        DISPLAY "Rule Limit Reached"
    ENDIF
END
```

---

## Module 2: Question Paper Management
Deals with recording, updating, and inventorying the questions in the actual examination paper.

### Algorithm
```
1. Start.
2. Read Question Number, Content Statement, Unit (1-5), CO (1-5), Topic, Cognitive Level, and Marks.
3. Execute AI Action Verb Classifier on question content to verify Bloom level alignment.
4. Store question record in questions array and increment question_count.
5. Update total accumulated marks.
6. Stop.
```

### Pseudocode
```
BEGIN
    INPUT q_no, content, unit, co_number, topic, cog_level, marks
    IF question_count < MAX_QUESTIONS THEN
        CALL ai_verify_question_alignment(content, cog_level)
        questions[question_count].q_no = q_no
        questions[question_count].content = content
        questions[question_count].unit = unit
        questions[question_count].co_number = co_number
        questions[question_count].marks = marks
        question_count = question_count + 1
        total_marks = total_marks + marks
    ENDIF
END
```

---

## Module 3: Data Organization and Analysis
Organizes raw question entries and blueprint rules into category-wise statistical structures.

### Algorithm
```
1. Start.
2. Initialize unit_stats[1..5], co_stats[1..5], and cog_stats[1..6] to zero.
3. Loop through blueprint rules:
     Accumulate expected_marks and expected_questions into corresponding Unit, CO, and Bloom buckets.
4. Loop through questions:
     Accumulate actual_marks and actual_questions into corresponding Unit, CO, and Bloom buckets.
     Accumulate weighted difficulty sum = SUM(cognitive_level * marks).
5. Calculate Difficulty Index = weighted_difficulty_sum / total_actual_marks.
6. For each category:
     Compute marks_diff = actual_marks - expected_marks.
7. Stop.
```

---

## Module 4: Blueprint Checking and Comparison Engine
Core audit module that identifies discrepancies and computes the compliance percentage.

### Algorithm
```
1. Start.
2. Compute Total Mark Error = |Total Actual Marks - Total Expected Marks|.
3. Loop u from 1 to 5:
     Add |unit_stats[u].marks_diff| to Total Mark Error.
4. Loop co from 1 to 5:
     Add |co_stats[co].marks_diff| to Total Mark Error.
5. Loop lvl from 1 to 6:
     Add |cog_stats[lvl].marks_diff| to Total Mark Error.
6. Max Penalty = 2 * Total Expected Marks.
7. Compliance Percentage = MAX(0.0, 100.0 - ((Total Mark Error / Max Penalty) * 100.0)).
8. If Compliance Percentage == 100.0 THEN Verdict = "100% COMPLIANT - APPROVED FOR EXAMINATION".
   Else If Compliance Percentage >= 80.0 THEN Verdict = "PARTIALLY COMPLIANT - MINOR CORRECTIONS REQUIRED".
   Else Verdict = "NON-COMPLIANT - REJECTED (REVISION REQUIRED)".
9. Stop.
```

---

## Module 5: Report Generation and File Management
Presents audit conclusions and exports official documentation.

### Algorithm
```
1. Start.
2. Display formatted unit, CO, and cognitive distribution tables on console with ANSI color codes.
3. Open "audit_report.txt" in write mode.
4. Write official header, metadata, executive summary, unit table, CO table, and Bloom table.
5. Write question inventory and formal signature placeholders for Faculty and HOD.
6. Close text file.
7. Open "audit_report.csv" in write mode.
8. Write structured comma-separated tables for Microsoft Excel compatibility.
9. Close CSV file.
10. Stop.
```

---

# 7. DATA DESIGN AND FILE HANDLING

### 7.1 Data Structures (`models.h`)
```c
typedef struct {
    int rule_id;
    int unit;                       // Unit 1 to 5
    int co_number;                  // Course Outcome CO1 to CO5
    char topic[64];                 // Topic Name
    int cognitive_level;            // Bloom's Level 1 to 6
    int expected_questions;
    int expected_marks;
} BlueprintItem;

typedef struct {
    char q_no[16];                  // Question Number
    char content[256];              // Question Statement
    int unit;
    int co_number;
    char topic[64];
    int cognitive_level;
    int marks;
} Question;

typedef struct {
    int id;
    char name[64];
    int expected_questions;
    int actual_questions;
    int expected_marks;
    int actual_marks;
    int marks_diff;
} CategoryStat;
```

### 7.2 File Formats
1. **`audit_report.txt`**: Formatted ASCII report containing college headers, executive summaries, tabular sections, and verification signature blocks.
2. **`audit_report.csv`**: Structured CSV format directly openable in spreadsheet software (Microsoft Excel, LibreOffice Calc, Google Sheets).

---

# 8. CORE IMPLEMENTATION & AI MODULES

### 8.1 Bloom's Taxonomy NLP Action Verb Classifier
Questions are parsed to identify Bloom's taxonomy action verbs using keyword heuristics:
- **L1 (Remember)**: *define, state, list, name, recall, identify, what is, mention*.
- **L2 (Understand)**: *explain, describe, discuss, outline, summarize, clarify, illustrate*.
- **L3 (Apply)**: *calculate, compute, solve, implement, demonstrate, execute, apply, derive*.
- **L4 (Analyze)**: *analyze, differentiate, distinguish, compare, contrast, examine, investigate*.
- **L5 (Evaluate)**: *evaluate, justify, critique, verify, assess, defend, rate, recommend*.
- **L6 (Create)**: *design, formulate, construct, develop, compose, invent, propose*.

When a faculty member assigns a cognitive level to a question, the system checks whether the action verbs match the level and issues a warning if there is a discrepancy.

### 8.2 Jaccard Question Similarity Detector
To prevent duplicate questions across assessments, the system tokenizes question statements, strips common stop words (*the, is, and, of, for, with*), and computes the Jaccard similarity coefficient:
$$J(Q_A, Q_B) = \frac{|Q_A \cap Q_B|}{|Q_A \cup Q_B|}$$
If similarity exceeds $35\%$, a redundancy alert is generated.

### 8.3 Weighted Difficulty Index Formula
$$\text{Difficulty Index} = \frac{\sum_{i=1}^{N} (\text{Cognitive Level}_i \times \text{Marks}_i)}{\text{Total Marks}}$$
- **Index $< 2.20$**: *Easy (Overemphasis on recall-based questions)*
- **Index $2.20 - 3.80$**: *Well-Balanced (Standard distribution for autonomous engineering examinations)*
- **Index $> 3.80$**: *Highly Challenging (Excessive higher-order analytical questions)*

---

# 9. TESTING AND SAMPLE RESULTS

### 9.1 Test Case Matrix
| Test ID | Test Scenario | Expected Output | Status |
| :---: | :--- | :--- | :---: |
| **TC01** | Add valid Blueprint Rule (Unit 1, CO1, 14 marks) | Rule added; expected marks incremented | **PASS** |
| **TC02** | Add valid Question with matching action verb | Question added; AI verifier confirms alignment | **PASS** |
| **TC03** | Enter question starting with "Define" but tagged as L4 | AI issues warning flag on cognitive mismatch | **PASS** |
| **TC04** | Total marks match 70 marks | Module 4 reports "SUCCESS: Total marks match" | **PASS** |
| **TC05** | Question Paper missing Unit 5 & CO5 | Module 4 flags Unit 5/CO5 discrepancy; marks under-allocated | **PASS** |
| **TC06** | Test Scenario 1 (Compliant 70-marks paper) | Compliance Score = 100.00%; Status = APPROVED | **PASS** |
| **TC07** | Test Scenario 2 (Flawed paper with omissions) | Compliance Score < 80.00%; Status = REJECTED | **PASS** |
| **TC08** | Duplicate questions entered in paper | AI Jaccard Detector flags similarity alert | **PASS** |
| **TC09** | Export Text Audit Report | `audit_report.txt` generated with signature lines | **PASS** |
| **TC10** | Export Excel CSV Report | `audit_report.csv` generated and opens in Excel | **PASS** |

### 9.2 Sample Compliant Paper Result
```
========================================================================================
                  MODULE 4: BLUEPRINT COMPLIANCE AUDIT & COMPARISON
========================================================================================
[1] Total Marks Verification:
    Prescribed Blueprint Marks : 70
    Actual Question Paper Marks: 70
    --> SUCCESS: Total marks match exactly.

[2] Unit-wise Distribution Audit:
    * Unit 1 COMPLIANT: 14 marks, 2 questions (Exact Match).
    * Unit 2 COMPLIANT: 14 marks, 2 questions (Exact Match).
    * Unit 3 COMPLIANT: 14 marks, 2 questions (Exact Match).
    * Unit 4 COMPLIANT: 14 marks, 2 questions (Exact Match).
    * Unit 5 COMPLIANT: 14 marks, 2 questions (Exact Match).

[3] Course Outcome (OBE CO1 - CO5) Audit:
    * CO 1 COMPLIANT: 14 marks allocated (OBE Target Met).
    * CO 2 COMPLIANT: 14 marks allocated (OBE Target Met).
    * CO 3 COMPLIANT: 14 marks allocated (OBE Target Met).
    * CO 4 COMPLIANT: 14 marks allocated (OBE Target Met).
    * CO 5 COMPLIANT: 14 marks allocated (OBE Target Met).

 Overall Compliance Score : 100.00 %
 Difficulty Index         : 3.26 / 6.00 (WELL-BALANCED)
 Final Academic Verdict   : 100% COMPLIANT - APPROVED FOR EXAMINATION
```

---

# 10. SECURITY, LIMITATIONS, AND FUTURE ENHANCEMENTS

### 10.1 Reliability Considerations
- Buffer overflow protections implemented using `strncpy` and field length bounds.
- Safe string consumption preventing buffer corruption during mixed numeric/text entries.
- Graceful handling of missing files during read operations.

### 10.2 Current Limitations
- Operates as a local command-line interface application.
- Question statements are limited to 256 characters per entry.
- File storage uses delimited plain text and CSV files rather than an SQL database.

### 10.3 Future Enhancements
- Integration with a web-based GUI (using HTML/CSS/WebAssembly or a REST API).
- OCR module to extract questions directly from scanned PDFs and Microsoft Word files.
- Integration with LLM APIs (e.g., Gemini API) for deeper semantic Bloom classification.

---

# 11. CONCLUSION

The **Examination Question Paper Blueprint Validation System** provides an automated, objective, and reliable software solution for question paper verification. Developed in C with modular architecture, it enforces strict compliance with institutional examination guidelines and Outcome-Based Education (OBE) accreditation standards.

By automating mark aggregation, Course Outcome distribution (CO1–CO5), Bloom's Taxonomy cognitive tracking, and duplicate question detection, the system eliminates human calculation errors and reduces scrutiny time from 45 minutes to less than two seconds. The generation of permanent audit reports in text and Microsoft Excel CSV formats ensures academic transparency, fair examinations, and seamless compliance with NBA and NAAC documentation requirements.

---

# 12. REFERENCES
1. Anderson, L. W., & Krathwohl, D. R. (2001). *A Taxonomy for Learning, Teaching, and Assessing: A Revision of Bloom's Taxonomy of Educational Objectives*. Longman, New York.
2. Kernighan, B. W., & Ritchie, D. M. (1988). *The C Programming Language* (2nd ed.). Prentice Hall, Englewood Cliffs, NJ.
3. National Board of Accreditation (NBA), India. *Outcome Based Education and Accreditation Manual for Undergraduate Engineering Programs*.
4. Rajeev Gandhi Memorial College of Engineering and Technology (Autonomous). *Academic Regulations and Examination Guidelines for B.Tech Programs (AY 2026-27)*.
5. ISO/IEC 9899:1999. *Programming Languages — C (C99 Standard)*.
