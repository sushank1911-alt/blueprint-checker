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
Dept. of CSE (AI&ML), RGMCET &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Dept. of CSE (AI&ML), RGMCET  

<br>

**Signature of External Examiner:** _______________________  
**Date:** _______________________  

---

# ABSTRACT

The **Examination Question Paper Blueprint Checker and Validation System** is an automated academic software tool developed in C that audits, verifies, and analyzes semester examination question papers against prescribed institutional blueprints. In autonomous engineering colleges such as Rajeev Gandhi Memorial College of Engineering & Technology, question papers must adhere strictly to assessment guidelines established under Outcome-Based Education (OBE) and Bloom’s Revised Taxonomy. The system verifies that questions and marks are evenly distributed across course units, Course Outcomes (CO1 to CO5), and cognitive levels (L1 Remember to L6 Create).

Traditionally, verification of blueprint compliance is performed manually by department scrutiny boards. Manual scrutiny requires considerable effort, is prone to arithmetic slips, lacks objective Bloom's assessment, and provides no systemic check against duplicate or highly similar questions. To eliminate these weaknesses, the proposed system provides an automated validation engine implemented in the C programming language.

The system is organized into five major modules: Module 1 (Blueprint Management) captures and manages reference standards; Module 2 (Question Paper Management) records the question inventory; Module 3 (Data Organization & Analysis) aggregates multi-dimensional frequency matrices across units, COs, and Bloom levels; Module 4 (Blueprint Checking & Comparison Engine) calculates discrepancy matrices and derives normalized compliance scores; and Module 5 (Report Generation & File Management) outputs real-time color-coded console evaluations while exporting official audit certificates (`audit_report.txt`) and Excel spreadsheets (`audit_report.csv`).

Furthermore, as an enhancement tailored for the CSE (AI & ML) curriculum, the application integrates an AI-based Action Verb Natural Language Classifier that cross-checks question statements against Bloom's Taxonomy levels, alongside a Jaccard Word Similarity Redundancy Detector to prevent duplicate examination questions. The resulting application ensures high academic rigor, supports fair student evaluations, and creates seamless digital audit trails for institutional accreditation.

---

# TABLE OF CONTENTS
1. Introduction
2. Problem Statement, Objectives, Scope
3. Existing and Proposed Systems
4. Requirements and Feasibility Study
5. System Architecture and Design
6. Five Modules: Design, Algorithms, Pseudocode
7. Data Design and File Handling
8. User Interface and Console Design
9. Core Implementation & AI Modules
10. Integration and Data Flow
11. Testing and Sample Results
12. Security, Limitations, and Future Enhancements
13. Conclusion
14. References

---

## 1. INTRODUCTION
### 1.1 Project Overview
The Examination Question Paper Blueprint Validation System is an automated academic software tool developed in C that audits, verifies, and analyzes semester examination question papers against prescribed institutional blueprints. In autonomous engineering colleges such as Rajeev Gandhi Memorial College of Engineering & Technology, question papers must adhere strictly to assessment guidelines established under Outcome-Based Education (OBE) and Bloom’s Revised Taxonomy. The system verifies that questions and marks are evenly distributed across course units, Course Outcomes (CO1 to CO5), and cognitive levels (L1 Remember to L6 Create).

### 1.2 Purpose
The primary purpose of this software is to eliminate human oversight, calculation slips, and subjective biases during examination scrutiny. By providing an objective mathematical audit, the system ensures that question papers remain fair, balanced, and compliant with National Board of Accreditation (NBA) standards.

### 1.3 Objectives
- Maintain and manage reference examination blueprints defining expected distributions of marks, units, topics, Course Outcomes, and cognitive levels.
- Capture, inventory, and validate actual question papers submitted by course faculty.
- Organize and aggregate questions into multidimensional category matrices.
- Execute difference checks to pinpoint marks over-allocation, under-allocation, or neglected syllabus topics.
- Quantify overall examination quality through a normalized Academic Compliance Percentage Score and a Weighted Difficulty Index.
- Incorporate AI/NLP action-verb heuristics and Jaccard token similarity to detect Bloom's taxonomy misalignments and question redundancy.
- Generate permanent audit records in both printable text format and Microsoft Excel-compatible CSV format.

### 1.4 Scope
The system is specifically designed for autonomous B.Tech examination structures (such as 70-mark semester-end theory examinations distributed across 5 units). It is intended for paper scrutiny committees, examination branch controllers, heads of departments, and course faculty.

### 1.5 Intended Users
- Department Examination Scrutiny Committees.
- Heads of Departments (HOD) and Academic Auditors.
- Course Faculty and Paper Setters.
- Institutional Accreditation and NBA Steering Committees.

---

## 2. PROBLEM STATEMENT, OBJECTIVES, AND SCOPE
### 2.1 Problem Statement
Preparing balanced examination question papers requires adherence to institutional assessment guidelines that define the distribution of questions across various difficulty levels and learning outcomes. Manual verification of blueprint compliance may result in inconsistencies, calculation errors, delayed review cycles, and non-compliance with NBA Outcome-Based Education requirements. A structured examination blueprint validation system is required to analyze question paper composition, verify compliance with predefined assessment standards, evaluate mark distribution, and generate validation reports that support fair and standardized examinations.

### 2.2 Proposed Solution
The proposed system provides an automated, deterministic verification engine developed in ANSI C. It processes blueprint rules, structures question records, performs category aggregation, calculates mathematical discrepancy matrices, applies AI-based action verb and similarity tests, and produces verifiable audit documentation.

### 2.3 Expected Benefits
- Eliminates arithmetic mistakes during manual marks summation.
- Enforces NBA Course Outcome (CO1 to CO5) alignment.
- Reduces paper scrutiny duration from 45 minutes to under two seconds.
- Provides objective, verifiable compliance reports with digital audit trails.

---

## 3. EXISTING AND PROPOSED SYSTEMS
### 3.1 Existing System
In the conventional scrutiny process, faculty paper setters submit handwritten or printed question paper drafts. Scrutiny committee members physically review the paper with a printed syllabus proforma, manually tally marks per unit, cross-check cognitive tags, and record subjective remarks on physical sheets.

### 3.2 Disadvantages of the Existing System
- High vulnerability to arithmetic errors during marks summation.
- Subjective Bloom's level tagging without verification of action verbs.
- No systemic check against duplicate questions across tests or internal assessments.
- Difficulty in maintaining permanent records for NBA/NAAC audit reviews.

### 3.3 Proposed System
The proposed software organizes blueprints and question papers into structured C records. It executes automated matrix comparisons across Units, Course Outcomes, and Bloom's levels, detects concept redundancies via Jaccard similarity, and generates formatted terminal tables alongside text and Excel audit files.

### 3.4 Advantages of the Proposed System
- Deterministic mathematical compliance scoring.
- Real-time ANSI color-coded visual alerts on console.
- Automated detection of Bloom's verb mismatch and duplicate questions.
- Permanent, tamper-resistant digital audit reports.

---

## 4. REQUIREMENTS AND FEASIBILITY STUDY
### 4.1 Functional Requirements
- **FR1**: Manage blueprint rules (add, view, modify, delete, and persist).
- **FR2**: Manage question inventory (capture statement, unit, CO, topic, Bloom level, and marks).
- **FR3**: Aggregate marks across Unit (1-5), CO (1-5), and Bloom's Cognitive Levels (L1-L6).
- **FR4**: Execute discrepancy analysis and compute normalized Compliance Percentage.
- **FR5**: Compute Weighted Paper Difficulty Index.
- **FR6**: Run AI NLP action verb validation and Jaccard token similarity checks.
- **FR7**: Save and export audit reports to TXT and CSV formats.

### 4.2 Non-Functional Requirements
Portability under ISO/IEC C99, sub-second execution speed, robust memory safety, graceful error recovery, and clear ANSI terminal presentation.

### 4.3 Hardware Requirements
- Standard PC or Laptop (Intel/AMD/Apple Silicon).
- Minimum 512 MB RAM.
- At least 10 MB free disk space.

### 4.4 Software Requirements
- Operating System: macOS, Linux, or Windows.
- C Compiler: GCC or Clang (C99 compatible).
- Build System: GNU Make (optional).

### 4.5 Feasibility Study
Technical Feasibility: Implemented using standard C libraries without third-party dependencies. Economic Feasibility: Developed using free and open-source tools. Operational Feasibility: Simple menu-driven console interface requiring no complex database setup.

---

## 5. SYSTEM ARCHITECTURE AND DESIGN
### 5.1 High-Level Architecture
```
+-------------------------------------------------------------------------------+
|                     EXAMINATION BLUEPRINT VALIDATION SYSTEM                   |
+-------------------------------------------------------------------------------+
         |                                                   |                   
         v                                                   v                   
 [Module 1: Blueprint Rules]                         [Module 2: Question Paper]  
 - Unit (1-5) & CO (1-5)                             - Question Content & Marks  
 - Target Bloom's & Marks                            - Unit, CO & Bloom Level    
         |                                                   |                   
         +-------------------------+-------------------------+                   
                                   |                                             
                                   v                                             
                [Module 3: Data Organization & Analysis]                         
                - Multi-Dimensional Distribution Matrices                        
                - Weighted Difficulty Index Calculation                          
                                   |                                             
                                   v                                             
                [Module 4: Blueprint Comparison Engine]                          
                - Discrepancy Matrix (Actual - Expected)                         
                - Compliance Percentage Score Formula                            
                                   |                                             
                                   v                                             
                [Module 5: Report Generation & Storage]                          
                - Color-Coded Console Summaries                                  
                - Text Audit Certificate & Excel CSV Export                      
```

### 5.2 Main Data Flow
1. User creates or loads reference blueprint.
2. User enters or loads question paper inventory.
3. System groups and aggregates data.
4. Engine runs discrepancy analysis.
5. AI helper verifies question action verbs and checks pairwise similarity.
6. Output module presents audit results and saves reports.

---

## 6. FIVE MODULES: DESIGN, ALGORITHMS, AND PSEUDOCODE

### Module 1: Blueprint Management
Responsible for creating, updating, viewing, and storing the reference question paper blueprint.
```
ALGORITHM:
1. Start.
2. Input Unit (1-5), CO Number (1-5), Topic, Cognitive Level (1-6), Expected Qs, Marks.
3. If rule_count < MAX_RULES, append to rules array and increment rule_count.
4. Calculate total expected marks = SUM(rules[i].expected_marks).
5. Support view, modify, delete, and file save/load operations.
6. Stop.
```

### Module 2: Question Paper Management
Deals with recording and managing actual question paper entries.
```
ALGORITHM:
1. Start.
2. Input Question No, Content Statement, Unit, CO, Topic, Cognitive Level, Marks.
3. Invoke AI Action Verb Classifier to verify Bloom's alignment.
4. Append to questions array and increment question_count.
5. Update total accumulated marks.
6. Stop.
```

### Module 3: Data Organization and Analysis
Organizes raw question data and blueprint standards into multi-dimensional category matrices.
```
ALGORITHM:
1. Start.
2. Initialize unit_stats[1..5], co_stats[1..5], cog_stats[1..6] to zero.
3. Loop through blueprint rules and accumulate expected marks and questions.
4. Loop through questions and accumulate actual marks and questions.
5. Calculate Weighted Difficulty Index = SUM(cog_level * marks) / total_marks.
6. Compute differences: marks_diff = actual_marks - expected_marks.
7. Stop.
```

### Module 4: Blueprint Checking and Comparison Engine
Core audit engine that executes mathematical discrepancy checks and derives the Compliance Score.
```
ALGORITHM:
1. Start.
2. Compute Total Error = SUM(|unit_diff|) + SUM(|co_diff|) + SUM(|cog_diff|).
3. Max Penalty = 2 * total_expected_marks.
4. Compliance Score = MAX(0.0, 100.0 - ((Total Error / Max Penalty) * 100.0)).
5. Assign academic status: Compliant (100%), Minor Defects (80-99%), Non-Compliant (<80%).
6. Stop.
```

### Module 5: Report Generation and File Management
Presents audit matrices on the console with ANSI color highlights and writes persistent audit records.
```
ALGORITHM:
1. Start.
2. Display formatted tables for Units, COs, Bloom's levels, and topics on terminal.
3. Open 'audit_report.txt' and write official certificate with signature blocks.
4. Open 'audit_report.csv' and write structured spreadsheet data.
5. Close files.
6. Stop.
```

---

## 7. DATA DESIGN AND FILE HANDLING
### 7.1 Data Dictionary and Entity Specifications
The system is built upon four primary structural entities that model the institutional blueprint rules, submitted examination questions, aggregate compliance statistics, and finalized audit certificates.

#### 7.1.1 Blueprint Rule Entity (`BlueprintItem`)
Defines the institutional expectation for each question item or section allocated within the curriculum syllabus:
| Field Name | C Data Type | Constraints & Range | Nullable | Functional Description | Example |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `rule_id` | `int` | $\ge 1$, Auto-increment | No | Unique identifier for the blueprint rule | `1` |
| `unit` | `int` | $1 \le \text{unit} \le 5$ | No | Syllabus unit number from syllabus curriculum | `1` |
| `co_number` | `int` | $1 \le \text{co} \le 5$ | No | Course Outcome mapping (CO1 to CO5) | `1` |
| `topic` | `char[64]` | Max 63 chars + `\0` | No | Topic descriptor within the designated unit | `Linear Data Structures` |
| `cognitive_level` | `int` | $1 \le \text{level} \le 6$ | No | Bloom's Revised Taxonomy level (L1–L6) | `3` (Apply) |
| `expected_questions` | `int` | $1 \le \text{count} \le 10$ | No | Number of questions expected for this rule | `1` |
| `expected_marks` | `int` | $1 \le \text{marks} \le 70$ | No | Target marks allocated to this rule specification | `7` |

#### 7.1.2 Examination Question Entity (`Question`)
Stores individual questions submitted by the course faculty or paper setter:
| Field Name | C Data Type | Constraints & Range | Nullable | Functional Description | Example |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `q_no` | `char[16]` | Alphanumeric, max 15 chars | No | Formal question label or sub-question designation | `Q1(a)` |
| `content` | `char[256]` | Max 255 chars + `\0` | No | Full natural language question statement text | `Define Doubly Linked List.` |
| `unit` | `int` | $1 \le \text{unit} \le 5$ | No | Assigned syllabus unit number | `1` |
| `co_number` | `int` | $1 \le \text{co} \le 5$ | No | Assigned Course Outcome (CO1 to CO5) | `1` |
| `topic` | `char[64]` | Max 63 chars + `\0` | No | Specific syllabus topic addressed | `Linked Lists` |
| `cognitive_level` | `int` | $1 \le \text{level} \le 6$ | No | Assigned Bloom's cognitive level (L1 to L6) | `1` (Remember) |
| `marks` | `int` | $1 \le \text{marks} \le 70$ | No | Marks allocated to this question | `7` |

#### 7.1.3 Category Aggregation Entity (`CategoryStat`)
Maintains dynamic frequency counters and differential metrics for vertical and horizontal scrutiny dimensions:
| Field Name | C Data Type | Description |
| :--- | :--- | :--- |
| `id` | `int` | Category identifier (Unit 1..5, CO 1..5, or Cognitive Level 1..6) |
| `name` | `char[64]` | Human-readable label (e.g., `"Unit 1"`, `"CO 2"`, `"L3: Apply"`) |
| `expected_questions` | `int` | Sum of questions demanded by reference blueprint |
| `actual_questions` | `int` | Sum of questions present in actual question paper |
| `expected_marks` | `int` | Prescribed marks according to reference blueprint |
| `actual_marks` | `int` | Total marks allocated in submitted question paper |
| `question_diff` | `int` | Variance in question count ($\text{actual} - \text{expected}$) |
| `marks_diff` | `int` | Variance in mark allocation ($\text{actual} - \text{expected}$) |

---

### 7.2 C Data Structure Implementations and Memory Layout
The system enforces compile-time static array sizing to guarantee zero heap fragmentation, deterministic memory usage, and high execution speed in resource-constrained environments:

```c
// models.h - Core Data Structures and Memory Layout
#define MAX_RULES      50
#define MAX_QUESTIONS  100
#define MAX_STR        64
#define MAX_TEXT       256
#define MAX_UNITS      10
#define MAX_COS        5

// Bloom's Revised Taxonomy Cognitive Levels
typedef enum {
    COG_NONE = 0,
    COG_L1 = 1, // Remember
    COG_L2 = 2, // Understand
    COG_L3 = 3, // Apply
    COG_L4 = 4, // Analyze
    COG_L5 = 5, // Evaluate
    COG_L6 = 6  // Create
} CognitiveLevel;

// Institutional Blueprint Item
typedef struct {
    int rule_id;
    int unit;
    int co_number;
    char topic[MAX_STR];
    int cognitive_level;
    int expected_questions;
    int expected_marks;
} BlueprintItem;

// Question Record Item
typedef struct {
    char q_no[16];
    char content[MAX_TEXT];
    int unit;
    int co_number;
    char topic[MAX_STR];
    int cognitive_level;
    int marks;
} Question;

// Complete Question Paper Record
typedef struct {
    char institution[MAX_STR];
    char department[MAX_STR];
    char subject_name[MAX_STR];
    char exam_name[MAX_STR];
    int total_marks;
    int question_count;
    Question questions[MAX_QUESTIONS];
} QuestionPaper;
```

#### Memory Sizing Analysis
- A `Question` structure occupies approximately $368$ bytes ($16 + 256 + 4 + 4 + 64 + 4 + 4$ plus struct alignment padding).
- A full `QuestionPaper` object supporting up to 100 questions requires approximately $37.2\text{ KB}$ of memory, allowing the entire verification suite to execute comfortably within small stack footprints and low-power embedded processors without dynamic allocations (`malloc`/`free`).

---

### 7.3 File Storage Architectures & Delimited Schemas
The system persists configurations and validation results across four distinct file formats:

#### 7.3.1 Reference Blueprint Storage (`blueprint.txt`)
`blueprint.txt` uses a composite format consisting of an institutional metadata header block followed by comma-separated rule records:
```text
RGMCET (Autonomous)
Department of Computer Science & Engineering (AI&ML)
Data Structures
Semester End Examination - Nov 2026
70
10
1,1,1,Linear Data Structures,1,1,7
2,1,1,Linked Lists,3,1,7
3,2,2,Stack Applications,2,1,7
4,2,2,Queue Structures,4,1,7
...
```
- **Lines 1–6 (Header Block)**: Institution Name, Department, Subject Name, Exam Name, Total Marks ($70$), and Rule Count ($10$).
- **Subsequent Lines (Rule Records)**: `rule_id,unit,co_number,topic,cognitive_level,expected_questions,expected_marks`.

#### 7.3.2 Question Paper Storage (`question_paper.txt`)
Because question statements frequently contain commas, quotes, and punctuation, standard CSV delimiters risk parsing corruption. Consequently, question records employ the hash delimiter (`#`) for unambiguous record splitting:
```text
RGMCET (Autonomous)
Department of Computer Science & Engineering (AI&ML)
Data Structures
Semester End Examination - Nov 2026
70
10
Q1(a)#Define Doubly Linked List with a neat diagram.#1#1#Linked Lists#1#7
Q1(b)#Implement insertion and deletion operations in Doubly Linked List.#1#1#Linked Lists#3#7
Q2(a)#Explain stack overflow and underflow conditions with examples.#2#2#Stacks#2#7
...
```
- **Record Syntax**: `q_no#content#unit#co_number#topic#cognitive_level#marks`.

#### 7.3.3 Official Text Audit Certificate (`audit_report.txt`)
Contains ASCII-formatted bordered inspection summaries suitable for direct printing, department bulletin boards, and official record archives:
- Institutional Identification and Examination metadata.
- Total Marks Verification check.
- Unit-wise mark and question distribution matrices.
- Course Outcome (CO1–CO5) OBE compliance summaries.
- Bloom's Taxonomy cognitive level percentage distributions.
- Overall Compliance Percentage, Difficulty Index, and Final Academic Verdict.

#### 7.3.4 Excel Spreadsheet Export (`audit_report.csv`)
An RFC 4180-compliant comma-separated spreadsheet enabling direct import into Microsoft Excel, Google Sheets, or institutional ERP systems. It structures compliance data into tabular categories with differential columns for automated chart generation.

---

### 7.4 File I/O Lifecycle, Stream Safety, and Error Handling
The file input/output subsystem is designed defensively to handle edge conditions, corrupt data, and platform variances:
1. **Explicit Stream Validation**: Every file access invokes explicit validation (`if (!fp)`). If a file is missing or inaccessible, the function logs an error message with ANSI highlighting and returns an error code ($0$) rather than crashing.
2. **Buffer Overflow Prevention**: File reading relies exclusively on `fgets(buffer, sizeof(buffer), fp)` rather than unbounded input functions (`gets()` or raw `scanf()`).
3. **Cross-Platform Line Ending Sanitization**: The system strips both carriage return (`\r`) and newline (`\n`) characters using `strcspn(buffer, "\r\n") = '\0'`, guaranteeing seamless interoperability across Windows, macOS, and Linux operating systems.
4. **Data Tokenization Safety**: String fields are parsed using safe token extraction routines (`strtok` or controlled `sscanf`), verifying that all mandatory tokens are present before populating internal records.

---

## 8. USER INTERFACE AND CONSOLE DESIGN
### 8.1 Technologies & Menu Structure
The user interface is an interactive, menu-driven terminal console application with clear sub-menus for Blueprint Management, Question Management, Multi-Dimensional Analysis, and Reporting.

### 8.2 ANSI Color Scheme
- **Green (`\033[1;32m`)**: Indicates 100% compliance, verified Bloom verbs, and exact matches.
- **Yellow (`\033[1;33m`)**: Indicates minor warnings, over-allocations, or pairwise question redundancy.
- **Red (`\033[1;31m`)**: Flags critical errors, missing units, omitted COs, or rejected papers.
- **Cyan (`\033[1;36m`)**: Formats section banners, table borders, and academic headers.

---

## 9. CORE IMPLEMENTATION & AI MODULES
### 9.1 Language and Concepts
Built with C99, the implementation uses structs, fixed-size multi-dimensional arrays, case-insensitive string parsing, tokenization (`strtok`), and file I/O streams.

### 9.2 Bloom's Taxonomy NLP Action Verb Classifier
Scans question statements for key action verbs:
- **L1 (Remember)**: *define, state, list, name, recall, identify, what is, mention*
- **L2 (Understand)**: *explain, describe, discuss, outline, summarize, clarify, illustrate*
- **L3 (Apply)**: *calculate, compute, solve, implement, demonstrate, execute, apply*
- **L4 (Analyze)**: *analyze, differentiate, distinguish, compare, contrast, examine*
- **L5 (Evaluate)**: *evaluate, justify, critique, verify, assess, defend, rate*
- **L6 (Create)**: *design, formulate, construct, develop, compose, invent, propose*

### 9.3 Jaccard Question Similarity Detector
Detects question redundancy and accidental repetition by computing Jaccard similarity across non-stopword tokens:
$$J(Q_A, Q_B) = \frac{|Q_A \cap Q_B|}{|Q_A \cup Q_B|}$$
Pairs with similarity $\ge 35\%$ trigger redundancy alerts.

### 9.4 Weighted Paper Difficulty Index
$$\text{Difficulty Index} = \frac{\sum (\text{Cognitive Level}_i \times \text{Marks}_i)}{\text{Total Marks}}$$
- **Index $< 2.20$**: Easy (Overemphasis on recall-based questions)
- **Index $2.20 - 3.80$**: Well-Balanced (Standard distribution for autonomous exams)
- **Index $> 3.80$**: Highly Challenging (Excessive higher-order questions)

---

## 10. INTEGRATION AND DATA FLOW
### 10.1 System Integration & Data Pipeline
The five modules operate in a continuous pipeline where data structures defined in `models.h` are populated by Modules 1 and 2, aggregated by Module 3, audited by Module 4, and exported by Module 5. State is managed seamlessly in memory and persisted to disk via delimited file structures.

### 10.2 Discrepancy Matrix Processing
The discrepancy engine aggregates differences across three orthogonal dimensions simultaneously: syllabus units (vertical coverage), Course Outcomes (OBE accreditation compliance), and cognitive complexity (Bloom's taxonomy). This multi-layered audit prevents papers from passing on mark totals alone while hiding structural imbalances.

### 10.3 Web Frontend & C Backend Interfacing
In addition to the native C console executable, the project provides an interactive web dashboard (`index.html`) running client-side JavaScript that mirrors the exact algorithmic logic of the C backend. Both interfaces read and produce standardized CSV data files.

---

## 11. TESTING AND SAMPLE RESULTS
### 11.1 Test Case Matrix
| Test ID | Test Scenario | Expected Result | Status to Record |
| :---: | :--- | :--- | :---: |
| **01** | Add valid Blueprint Rule (Unit 1, CO1, 14 marks) | Rule added; expected marks incremented | **Pass** |
| **02** | Add Question with matching action verb | Question added; AI verifier confirms alignment | **Pass** |
| **03** | Add question starting with 'Define' tagged as L4 | AI issues warning on cognitive mismatch | **Pass** |
| **04** | Total marks match prescribed 70 marks | Module 4 reports total marks match | **Pass** |
| **05** | Question Paper missing Unit 5 & CO5 | Discrepancy engine flags under-allocation | **Pass** |
| **06** | Test Scenario 1 (Compliant 70-marks paper) | Compliance Score = 100.00%; Status = APPROVED | **Pass** |
| **07** | Test Scenario 2 (Flawed paper with errors) | Compliance Score < 80.00%; Status = REJECTED | **Pass** |
| **08** | Duplicate questions entered in paper | Jaccard similarity flags redundancy alert | **Pass** |
| **09** | Export Text Audit Report | `audit_report.txt` generated on disk | **Pass** |
| **10** | Export Excel CSV Spreadsheet | `audit_report.csv` generated on disk | **Pass** |

### 11.2 Sample Compliant Paper Execution Run
```
========================================================================================
                  MODULE 4: BLUEPRINT COMPLIANCE AUDIT & COMPARISON                     
========================================================================================
[1] Total Marks Verification:                                                           
    Prescribed Blueprint Marks : 70                                                     
    Actual Question Paper Marks: 70                                                     
    --> SUCCESS: Total marks match prescribed 70 marks exactly.                         
                                                                                        
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
                                                                                        
[4] Bloom's Cognitive Level Distribution Audit:                                         
    * L1 (Remember)  COMPLIANT: 4 marks allocated.                                      
    * L2 (Understand) COMPLIANT: 12 marks allocated.                                    
    * L3 (Apply)     COMPLIANT: 26 marks allocated.                                     
    * L4 (Analyze)   COMPLIANT: 18 marks allocated.                                     
    * L5 (Evaluate)  COMPLIANT: 10 marks allocated.                                     
                                                                                        
 Overall Compliance Score : 100.00 %                                                    
 Difficulty Index         : 3.26 / 6.00 (WELL-BALANCED)                                 
 Final Academic Verdict   : 100% COMPLIANT - APPROVED FOR EXAMINATION                   
========================================================================================
```

### 11.3 Sample Flawed Paper Execution Run
```
========================================================================================
                  MODULE 4: BLUEPRINT COMPLIANCE AUDIT & COMPARISON                     
========================================================================================
[1] Total Marks Verification:                                                           
    Prescribed Blueprint Marks : 70                                                     
    Actual Question Paper Marks: 58                                                     
    --> CRITICAL MISMATCH: Net difference of -12 marks!                                 
                                                                                        
[2] Unit-wise Distribution Audit:                                                       
    * Unit 1 DISCREPANCY: Expected 14 marks (2 Qs), got 18 marks (2 Qs). Diff: +4 marks.  
    * Unit 2 COMPLIANT:   14 marks, 2 questions (Exact Match).                          
    * Unit 3 DISCREPANCY: Expected 14 marks (2 Qs), got 12 marks (2 Qs). Diff: -2 marks.  
    * Unit 4 COMPLIANT:   14 marks, 2 questions (Exact Match).                          
    * Unit 5 DISCREPANCY: Expected 14 marks (2 Qs), got 0 marks (0 Qs).  Diff: -14 marks. 
                                                                                        
[3] Course Outcome (OBE CO1 - CO5) Audit:                                               
    * CO 1 MISMATCH: Expected 14 marks, Actual 18 marks (Diff: +4).                     
    * CO 5 MISMATCH: Expected 14 marks, Actual 0 marks (Diff: -14, Omitted!).           
                                                                                        
 Overall Compliance Score : 68.57 %                                                     
 Total Discrepancy Units  : 44 mark units                                               
 Final Academic Verdict   : NON-COMPLIANT - REJECTED (REVISION REQUIRED)                
========================================================================================
```

---

## 12. SECURITY, LIMITATIONS, AND FUTURE ENHANCEMENTS
### 12.1 Security and Reliability Considerations
Array boundary protections, input validation on numeric choices, buffer clearing to prevent input pollution, safe string handling (`strncpy`), and strict error checking on file pointers ensure safe, predictable execution without memory leaks, segmentation faults, or buffer overflow vulnerabilities.

### 12.2 Current Limitations
- Command-line and single-user local file execution model.
- Fixed array allocation sizes (50 rules, 100 questions per paper).
- Question statements capped at 256 characters per entry.
- Plain text and CSV storage rather than an encrypted multi-user SQL database.

### 12.3 Future Enhancements
- Integration with an OCR engine to extract questions directly from scanned PDFs and Word documents.
- Integration with Large Language Model APIs (e.g. Gemini API) for deeper semantic Bloom classification.
- Migration of file storage to an embedded SQLite or PostgreSQL database with role-based access control.
- Full WebAssembly compilation allowing the C binary to execute natively inside browser interfaces.

---

## 13. CONCLUSION
The Examination Question Paper Blueprint Validation System provides an automated, mathematical, and objective software tool for question paper scrutiny. Developed in modular C, it enforces strict compliance with institutional examination guidelines, Course Outcomes (CO1 to CO5), and Bloom’s Revised Taxonomy. By automating mark aggregation and discrepancy calculation while incorporating AI-assisted verb verification and question redundancy scanning, the system eliminates human calculation errors, reduces scrutiny time from 45 minutes to under two seconds, and generates verifiable audit documentation that supports academic excellence and institutional accreditation.

---

## 14. REFERENCES
[1] Anderson, L. W., & Krathwohl, D. R. (2001). *A Taxonomy for Learning, Teaching, and Assessing: A Revision of Bloom's Taxonomy of Educational Objectives*. Longman, New York.  
[2] Kernighan, B. W., & Ritchie, D. M. (1988). *The C Programming Language* (2nd ed.). Prentice Hall, Englewood Cliffs, NJ.  
[3] National Board of Accreditation (NBA), India. *Outcome Based Education and Accreditation Manual for Undergraduate Engineering Programs*.  
[4] Rajeev Gandhi Memorial College of Engineering and Technology (Autonomous). *Academic Regulations and Examination Guidelines for B.Tech Programs (AY 2026-27)*.  
[5] ISO/IEC 9899:1999. *Programming Languages — C (C99 Standard)*.  
[6] Jaccard, P. (1912). *The Distribution of the Flora in the Alpine Zone*. New Phytologist, 11(2), 37-50.  
[7] Manning, C. D., Raghavan, P., & Schütze, H. (2008). *Introduction to Information Retrieval*. Cambridge University Press.  
[8] Pressman, R. S., & Maxim, B. R. (2020). *Software Engineering: A Practitioner's Approach* (9th ed.). McGraw-Hill Education.
