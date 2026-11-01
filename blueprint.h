#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include "models.h"

// Module 1: Blueprint Management Functions
void init_blueprint(Blueprint *bp);
int add_blueprint_rule(Blueprint *bp, int unit, int co_number, const char *topic, int cog_level, int exp_q, int exp_marks);
void view_blueprint(const Blueprint *bp);
int modify_blueprint_rule(Blueprint *bp, int rule_id);
int delete_blueprint_rule(Blueprint *bp, int rule_id);
int calculate_blueprint_total_marks(Blueprint *bp);
int save_blueprint_to_file(const Blueprint *bp, const char *filename);
int load_blueprint_from_file(Blueprint *bp, const char *filename);
void load_default_rgm_blueprint(Blueprint *bp);

#endif // BLUEPRINT_H
