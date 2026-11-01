#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ai_helper.h"

// Case-insensitive substring search helper
static int contains_word(const char *haystack, const char *needle) {
    char lower_haystack[MAX_TEXT];
    char lower_needle[MAX_STR];
    size_t i;

    for (i = 0; i < sizeof(lower_haystack) - 1 && haystack[i] != '\0'; i++) {
        lower_haystack[i] = (char)tolower((unsigned char)haystack[i]);
    }
    lower_haystack[i] = '\0';

    for (i = 0; i < sizeof(lower_needle) - 1 && needle[i] != '\0'; i++) {
        lower_needle[i] = (char)tolower((unsigned char)needle[i]);
    }
    lower_needle[i] = '\0';

    return (strstr(lower_haystack, lower_needle) != NULL);
}

// Rule-based Bloom's Taxonomy NLP action verb classifier
int ai_predict_cognitive_level(const char *question_text) {
    // L6 (Create) keywords
    const char *l6_words[] = {"design", "formulate", "construct", "develop", "compose", "invent", "propose", "synthesize", NULL};
    // L5 (Evaluate) keywords
    const char *l5_words[] = {"evaluate", "justify", "critique", "verify", "assess", "defend", "rate", "recommend", NULL};
    // L4 (Analyze) keywords
    const char *l4_words[] = {"analyze", "differentiate", "distinguish", "compare", "contrast", "examine", "investigate", "breakdown", NULL};
    // L3 (Apply) keywords
    const char *l3_words[] = {"calculate", "compute", "solve", "implement", "demonstrate", "execute", "apply", "derive", NULL};
    // L2 (Understand) keywords
    const char *l2_words[] = {"explain", "describe", "discuss", "outline", "summarize", "clarify", "illustrate", "why does", "how does", NULL};
    // L1 (Remember) keywords
    const char *l1_words[] = {"define", "state", "list", "name", "recall", "identify", "what is", "mention", "enlist", NULL};

    int i;
    for (i = 0; l6_words[i] != NULL; i++) {
        if (contains_word(question_text, l6_words[i])) return COG_L6;
    }
    for (i = 0; l5_words[i] != NULL; i++) {
        if (contains_word(question_text, l5_words[i])) return COG_L5;
    }
    for (i = 0; l4_words[i] != NULL; i++) {
        if (contains_word(question_text, l4_words[i])) return COG_L4;
    }
    for (i = 0; l3_words[i] != NULL; i++) {
        if (contains_word(question_text, l3_words[i])) return COG_L3;
    }
    for (i = 0; l2_words[i] != NULL; i++) {
        if (contains_word(question_text, l2_words[i])) return COG_L2;
    }
    for (i = 0; l1_words[i] != NULL; i++) {
        if (contains_word(question_text, l1_words[i])) return COG_L1;
    }

    return COG_NONE;
}

void ai_verify_question_alignment(const Question *q) {
    int predicted = ai_predict_cognitive_level(q->content);
    if (predicted == COG_NONE) {
        printf("   %s[AI Assist]%s No specific action verb detected. Preserving assigned %s.\n",
               COLOR_CYAN, COLOR_RESET, get_cognitive_name(q->cognitive_level));
        return;
    }

    if (predicted == q->cognitive_level) {
        printf("   %s[AI Assist Verified]%s Action verbs strongly align with %s.\n",
               COLOR_GREEN, COLOR_RESET, get_cognitive_name(q->cognitive_level));
    } else {
        printf("   %s[AI Assist WARNING]%s Action verbs suggest %s (%s), but tagged as %s (%s).\n",
               COLOR_YELLOW, COLOR_RESET,
               get_cognitive_name(predicted), get_cognitive_desc(predicted),
               get_cognitive_name(q->cognitive_level), get_cognitive_desc(q->cognitive_level));
    }
}

// Common stop-words to ignore during similarity analysis
static int is_stopword(const char *word) {
    const char *stopwords[] = {
        "the", "is", "at", "which", "on", "a", "an", "and", "or", "in", "to",
        "of", "for", "with", "by", "as", "from", "that", "this", "it", "are",
        "was", "were", "be", "been", "have", "has", "had", "do", "does", "did", NULL
    };
    for (int i = 0; stopwords[i] != NULL; i++) {
        if (strcmp(word, stopwords[i]) == 0) return 1;
    }
    return 0;
}

// Tokenize text into lowercased clean words
static int extract_tokens(const char *text, char words[64][32]) {
    int count = 0;
    char buffer[MAX_TEXT];
    size_t len = strlen(text);
    if (len >= sizeof(buffer)) len = sizeof(buffer) - 1;

    for (size_t i = 0; i < len; i++) {
        char c = text[i];
        if (isalnum((unsigned char)c)) {
            buffer[i] = (char)tolower((unsigned char)c);
        } else {
            buffer[i] = ' '; // replace punctuation with space
        }
    }
    buffer[len] = '\0';

    char *tok = strtok(buffer, " ");
    while (tok && count < 64) {
        if (strlen(tok) > 2 && !is_stopword(tok)) {
            // Check if already in words
            int exists = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(words[i], tok) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                strncpy(words[count], tok, 31);
                words[count][31] = '\0';
                count++;
            }
        }
        tok = strtok(NULL, " ");
    }
    return count;
}

// Computes Jaccard Similarity between two questions
static float compute_jaccard_similarity(const char *text1, const char *text2) {
    char words1[64][32];
    char words2[64][32];
    int count1 = extract_tokens(text1, words1);
    int count2 = extract_tokens(text2, words2);

    if (count1 == 0 || count2 == 0) return 0.0f;

    int intersection = 0;
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                intersection++;
                break;
            }
        }
    }

    int union_size = (count1 + count2) - intersection;
    if (union_size <= 0) return 0.0f;

    return (float)intersection / (float)union_size;
}

// Scans all pairs of questions in the paper for high similarity
int ai_check_question_similarity(const QuestionPaper *qp, float threshold) {
    int flagged_pairs = 0;
    printf("\n========================================================================================\n");
    printf("         %sAI FEATURE: QUESTION SIMILARITY & REDUNDANCY DETECTOR (JACCARD)%s\n", COLOR_CYAN, COLOR_RESET);
    printf("========================================================================================\n");

    if (qp->question_count < 2) {
        printf("Not enough questions to perform pairwise similarity check.\n");
        return 0;
    }

    for (int i = 0; i < qp->question_count; i++) {
        for (int j = i + 1; j < qp->question_count; j++) {
            float sim = compute_jaccard_similarity(qp->questions[i].content, qp->questions[j].content);
            if (sim >= threshold) {
                flagged_pairs++;
                printf(" %s[SIMILARITY ALERT (%.1f%%)]%s Questions %s and %s share high concept overlap:\n",
                       COLOR_YELLOW, sim * 100.0f, COLOR_RESET,
                       qp->questions[i].q_no, qp->questions[j].q_no);
                printf("   - %s: \"%s\"\n", qp->questions[i].q_no, qp->questions[i].content);
                printf("   - %s: \"%s\"\n", qp->questions[j].q_no, qp->questions[j].content);
            }
        }
    }

    if (flagged_pairs == 0) {
        printf(" %s[PASSED]%s No redundant or duplicated questions detected across the paper.\n",
               COLOR_GREEN, COLOR_RESET);
    } else {
        printf(" %s[AUDIT FLAG]%s %d question pair(s) flagged for potential redundancy.\n",
               COLOR_YELLOW, COLOR_RESET, flagged_pairs);
    }
    printf("========================================================================================\n");
    return flagged_pairs;
}
