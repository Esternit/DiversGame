#pragma once

struct FrameAnimation {
	int FrameX;
	int StepX;
	int FrameY;
	int StepY;

	FrameAnimation(int FrameX, int StepX, int FrameY, int StepY) : FrameX(FrameX), StepX(StepX), FrameY(FrameY), StepY(StepY) {}
};

