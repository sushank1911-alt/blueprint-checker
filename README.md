# Examination Question Paper Blueprint Validation System

**Institution**: RGM College of Engineering and Technology (Autonomous), Nandyal  
**Department**: Department of Computer Science & Engineering (Artificial Intelligence & Machine Learning)  
**Academic Year**: AY 2026-27 | II B.Tech I Semester  
**Course Assignment Project**: Blueprint Checker  

---

## 1. Problem Statement
Preparing balanced examination question papers requires strict adherence to institutional assessment guidelines defining the distribution of questions across learning outcomes (Bloom's Taxonomy) and Course Outcomes (CO1 to CO5). Manual verification of blueprint compliance is prone to inconsistencies, oversights, and human errors. 

This project implements an automated, structured **Examination Blueprint Validation System in C** to:
1. Analyze question paper composition across units, topics, and cognitive levels.
2. Verify Outcome-Based Education (OBE) compliance across Course Outcomes (**CO1 to CO5**).
3. Compute a quantitative **Paper Difficulty Index**.
4. Detect duplicate or redundant questions using **Jaccard Word Similarity** (AI/ML feature).
5. Generate official audit certificates in formatted text (`audit_report.txt`) and Microsoft Excel spreadsheet (`audit_report.csv`).

---

## 2. Project Architecture & Module Mapping

| Module | Source Files | Purpose & Key Features |
| :--- | :--- | :--- |
| **Module 1: Blueprint Management** | `blueprint.h`, `blueprint.c` | Defines and manages reference standards (units 1–5, Course Outcomes CO1–CO5, Bloom's L1–L6, expected questions, and marks). Supports adding, viewing, modifying, and disk persistence. |
| **Module 2: Question Paper Management** | `question_paper.h`, `question_paper.c` | Captures examination questions (`q_no`, content, unit, CO number, topic, cognitive level, marks). |
| **Module 3: Data Organization & Analysis** | `analysis.h`, `analysis.c` | Multi-dimensional aggregation: Unit-wise, Course Outcome-wise (CO1–CO5), Bloom's taxonomy, and calculates the weighted **Difficulty Index** ($1.00$ to $6.00$). |
| **Module 4: Blueprint Checking & Comparison Engine** | `checker.h`, `checker.c` | Computes mark and question discrepancies ($\Delta = \text{Actual} - \text{Expected}$), checks OBE targets, flags mismatches, and calculates the **Academic Compliance Score (%)**. |
| **Module 5: Report Generation & File Management** | `report.h`, `report.c` | Outputs ANSI color-coded console reports and exports: (1) Printable audit certificate `audit_report.txt`, (2) Microsoft Excel CSV spreadsheet `audit_report.csv`. |
| **AI/ML Module: Bloom's & Jaccard Analyzer** | `ai_helper.h`, `ai_helper.c` | (a) **Bloom's Action Verb Classifier**: Auto-suggests and validates cognitive levels from question text.<br>(b) **Jaccard Similarity Detector**: Scans question pairs to detect concept redundancy and duplicate questions. |

---

## 3. Mathematical Formulas Used

1. **Category Discrepancy**:
   $$\text{Marks Diff} = \text{Actual Marks} - \text{Expected Marks}$$

2. **Weighted Paper Difficulty Index**:
   $$\text{Difficulty Index} = \frac{\sum_{i=1}^{N} (\text{Cognitive Level}_i \times \text{Marks}_i)}{\text{Total Marks}}$$
   - $< 2.20$: **EASY** (Heavy Lower-Order Thinking)
   - $2.20 - 3.80$: **WELL-BALANCED** (Recommended for Autonomous Exams)
   - $> 3.80$: **HIGHLY CHALLENGING** (Excessive Higher-Order Thinking)

3. **Academic Compliance Percentage Score**:
   $$\text{Compliance Score (\%)} = \max\left(0.0,\, 100.0 - \left(\frac{\sum |\text{Actual Marks} - \text{Expected Marks}|}{2 \times \text{Total Expected Marks}} \times 100.0\right)\right)$$

4. **Jaccard Question Similarity**:
   $$J(Q_A, Q_B) = \frac{|Q_A \cap Q_B|}{|Q_A \cup Q_B|}$$

---

## 4. How to Compile and Run

In your terminal:

```bash
cd /Users/irfan/sushank

# Compile using Makefile
make

# Run the system
./blueprint_checker
```

Or compile manually:
```bash
clang -Wall -Wextra -std=c99 -o blueprint_checker *.c
./blueprint_checker
```

---

## 5. Main Menu Quick Reference

1. **Option 1**: Blueprint Management (Define or inspect rules, units, COs, and target marks).
2. **Option 2**: Question Paper Management (Enter questions with AI assistance).
3. **Option 3**: Data Organization & Analysis (View unit, CO, Bloom's, and topic summaries).
4. **Option 4**: Run Compliance Engine (Runs discrepancy checks and generates compliance score).
5. **Option 5**: View Audit Report & Export to `.txt` and `.csv` (Excel).
6. **Option 6**: **AI Feature** — Question Similarity & Duplicate Detector.
7. **Option 7**: Test Scenario 1 (Compliant 70-marks paper $\rightarrow$ 100% Score).
8. **Option 8**: Test Scenario 2 (Flawed paper with errors $\rightarrow$ Discrepancy flags).
