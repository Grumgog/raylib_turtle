#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

typedef struct TurtleState {
	int posX;
	int posY;
	double rotation;
	bool isPenDown;
	Color color;
	Image* image;
} TurtleState;

typedef struct {
	struct TurtleState;
} Turtle;


static void _Noreturn MEM_ALLOC_ERROR(void) {
	puts("CANNOT ALLOCATE MEMORY!");
	exit(-1);
}

static void CLIP_TURTLE_ROTATION(TurtleState* state) {
	int r = (int)floor(state->rotation / (2 * PI));
	state->rotation = state->rotation - (r * (2 * PI));
}

Turtle* Turtle_newTurtle(void) {
	Turtle *turtle = (Turtle*)malloc(sizeof(Turtle));
	if (turtle == NULL) {
		MEM_ALLOC_ERROR();
	}
	turtle->posX = 0;
	turtle->posY = 0;
	turtle->rotation = 0;
	turtle->isPenDown = false;
	turtle->color = RED;
	turtle->image = NULL;

	return turtle;
}

static void ASSIGN_TURTLE_STATE(TurtleState* target, TurtleState *source) {
	target->posX = source->posX;
	target->posY = source->posY;
	target->color = source->color;
	target->isPenDown = source->isPenDown;
	target->rotation = source->rotation;
	target->image = source->image;
}

TurtleState* Turtle_GetTurtleState(Turtle* turtle) {
	TurtleState* state = (TurtleState*)malloc(sizeof(TurtleState));
	ASSIGN_TURTLE_STATE(state, (TurtleState*)turtle);
	return state;
}

void Turtle_freeTurtleState(TurtleState* state) {
	free(state);
}

void Turtle_freeTurtle(TurtleState *turtle) {
	if (turtle != NULL) 
		free(turtle);
}

void Turtle_assinImage(Turtle* turtle, Image* image) {
	turtle->image = image;
}

void Turtle_penDown(TurtleState* t) {
	t->isPenDown = true;
}

void Turtle_penUp(TurtleState* t) {
	t->isPenDown = false;
}

void static MOVE_FORWARD(int *posX, int *posY, double rotation, size_t distance) {
	double dirX = cos(rotation);
	double dirY = sin(rotation);

	double shiftX = dirX * distance;
	double shiftY = dirY * distance;

	*posX += (int)shiftX;
	*posY += (int)shiftY;
}

void Turtle_moveForward(TurtleState* t, size_t distance) {
	int posX = t->posX;
	int posY = t->posY;

	MOVE_FORWARD(&t->posX, &t->posY, t->rotation, distance);

	if (t->isPenDown) {
		DrawLine(posX, posY, t->posX, t->posY, t->color);
	}
}

void Turtle_moveBackward(TurtleState* t, size_t distance) {
	int posX = t->posX;
	int posY = t->posY;

	MOVE_FORWARD(&t->posX, &t->posY, t->rotation, -distance);

	if (t->isPenDown) {
		DrawLine(posX, posY, t->posX, t->posY, t->color);
	}
}

void Turtle_setRotation(TurtleState* state, double rotation) {
	state->rotation = rotation;
	CLIP_TURTLE_ROTATION(state);
}

void Turtle_rotateRight(TurtleState* state, double rotation) {
	state->rotation += rotation;
	CLIP_TURTLE_ROTATION(state);
}

void Turtle_rotateLeft(TurtleState* state, double rotation) {
	state->rotation -= rotation;
	CLIP_TURTLE_ROTATION(state);
}

void Turtle_setPosition(TurtleState* state, int posX, int posY) {
	state->posX = posX;
	state->posY = posY;
}

void Turtle_shiftPosition(Turtle* state, int shiftX, int shiftY) {
	state->posX += shiftX;
	state->posY += shiftY;
}

