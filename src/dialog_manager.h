#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <stdbool.h>

void dialog_init(void);
bool dialog_can_start(void);
void dialog_start(const char **dialogPages, int numPages);
bool dialog_update(bool now2nd); // Modified to accept key state
void dialog_draw(void);
bool dialog_is_active(void);
bool dialog_is_in_delay(void);

#endif