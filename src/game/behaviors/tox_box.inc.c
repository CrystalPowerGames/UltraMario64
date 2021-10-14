// tox_box.c.inc

s8 sToxBoxDirectionPattern1[] = { 4, 1, 4, 1, 6, 1, 6, 1, 5, 1, 5, 1, 6, 1, 6, 1, 5, 1, 2, 4, 1, 4, 1, 4, 1, 2,
                                  5, 1, 5, 1, 7, 1, 7, 1, 4, 1, 4, 1, 7, 1, 7, 1, 5, 1, 5, 1, 5, 1, 2, 4, 1, -1 };
s8 sToxBoxDirectionPattern2[] = { 4, 1, 4, 1, 7, 1, 7, 1, 7, 1, 2, 6, 1, 6, 1, 6, 1, 5,
                                  1, 5, 1, 6, 1, 5, 1, 5, 1, 2, 4, 1, 4, 1, 7, 1, -1 };
s8 sToxBoxDirectionPattern3[] = { 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 2, 5, 1, 5, 1, 5, 1, 5,
                                  1, 5, 1, 7, 1, 2, 6, 1, 6, 1, 5, 1, 2, 4, 1, 7, 1, -1 };
s8 *sToxBoxDirectionPatterns[] = { sToxBoxDirectionPattern1, sToxBoxDirectionPattern2, sToxBoxDirectionPattern3 };

void tox_box_shake_screen(void) {
    if (o->oDistanceToMario < 3000.0f) {
        cur_obj_shake_screen(SHAKE_POS_SMALL);
    }
}

void tox_box_move(f32 forwardVel, f32 leftVel, s16 deltaPitch, s16 deltaRoll) {
    o->oPosY = 99.41124f * sins((f32)(o->oTimer + 1) / 8 * 0x8000) + o->oHomeY + 3.0f;
    o->oForwardVel = forwardVel;
    o->oLeftVel = leftVel;
    o->oFaceAnglePitch += deltaPitch;
    if ((s16) o->oFaceAnglePitch < 0)
        deltaRoll = -deltaRoll;
    o->oFaceAngleRoll += deltaRoll;
    cur_obj_set_pos_via_transform();
    if (o->oTimer == 7) {
        o->oAction = cur_obj_progress_direction_table();
        cur_obj_play_sound_2(SOUND_GENERAL_TOX_BOX_MOVE);
    }
}

void tox_box_act_4(void) {
    tox_box_move(64.0f, 0.0f, 0x800, 0);
}
void tox_box_act_5(void) {
    tox_box_move(-64.0f, 0.0f, -0x800, 0);
}
void tox_box_act_6(void) {
    tox_box_move(0.0f, -64.0f, 0, 0x800);
}
void tox_box_act_7(void) {
    tox_box_move(0.0f, 64.0f, 0, -0x800);
}

void tox_box_act_1(void) {
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0)
        tox_box_shake_screen();
    o->oPosY = o->oHomeY + 3.0f;
    if (o->oTimer == 20)
        o->oAction = cur_obj_progress_direction_table();
}

void tox_box_act_2(void) {
    if (o->oTimer == 20)
        o->oAction = cur_obj_progress_direction_table();
}

void tox_box_act_3(void) {
    if (o->oTimer == 20)
        o->oAction = cur_obj_progress_direction_table();
}

void tox_box_act_0(void) {
    s8 *pattern = sToxBoxDirectionPatterns[o->oBehParams2ndByte];
    o->oAction = cur_obj_set_direction_table(pattern);
}

void (*sToxBoxActions[])(void) = { tox_box_act_0, tox_box_act_1, tox_box_act_2, tox_box_act_3,
                                   tox_box_act_4, tox_box_act_5, tox_box_act_6, tox_box_act_7 };

void bhv_tox_box_loop(void) {
    cur_obj_call_action_function(sToxBoxActions);
    load_object_collision_model();
}
