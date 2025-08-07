// dialog_manager.h
#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <tice.h>
#include <graphx.h>
#include <stdbool.h>

enum emotion { SMILE, SAD, }; // Define enum first
extern enum emotion emotion; // Declare global variable

void dialog_init(void);
bool dialog_is_active(void);
bool dialog_is_in_delay(void);
void dialog_start(const char **dialogPages, int numPages);
bool dialog_update(bool now2nd);
void dialog_draw(void);

#endif