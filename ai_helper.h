#ifndef AI_HELPER_H
#define AI_HELPER_H

#include "models.h"

// 1. NLP Rule-based Action Verb Classifier for Bloom's Taxonomy
int ai_predict_cognitive_level(const char *question_text);

// 2. Alignment Validator (checks question text verbs vs assigned level)
void ai_verify_question_alignment(const Question *q);

// 3. Question Redundancy & Duplicate Detector (Jaccard Word Similarity)
int ai_check_question_similarity(const QuestionPaper *qp, float threshold);

#endif // AI_HELPER_H
