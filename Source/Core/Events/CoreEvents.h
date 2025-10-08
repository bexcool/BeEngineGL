//
// Created by Petr Pavlík on 08.10.2025.
//

#ifndef COREEVENTS_H
#define COREEVENTS_H

#define DEFINE_VIRTUAL_COREEVENTS \
virtual void OnRendered();\
virtual void OnTick();

#define DEFINE_VIRTUAL_KEYEVENTS \
virtual void OnKeyboardKeyEvent(KeyboardKeyEventArgs e);\
virtual void OnMouseKeyEvent(MouseKeyEventArgs e);

#define DECLARE_VIRTUAL_COREEVENTS(className) \
void className::OnRendered() {} \
void className::OnTick() {}

#endif //COREEVENTS_H
