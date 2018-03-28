#include"Camera.h"
#include"GameSystem.h"

CameraManager::CameraManager(Vec2 player) :
	pos(Window::Center() - player),
	t_pos(Window::Center() - player),
	scale(1.0),
	t_scale(1.0),
	ease(0.8) {
}

void CameraManager::update(Vec2 player) {
	//�ʒu
	t_pos = Window::Center() - player;
	//�K����y���W�Œ�
	//t_pos.y = Window::Center().y - 340.0 / 100.0;
	t_pos.y += 100.0 / 100.0;
	//�g��k��
	if (GameSystem::get().input.zoomIn.clicked && t_scale < 1.3) {
		t_scale += 0.2;
	}
	if (GameSystem::get().input.zoomOut.clicked && t_scale > 0.7) {
		t_scale -= 0.2;
	}
	//�C�[�Y����
	pos = ease * pos + (1 - ease) * t_pos;
	scale = ease * scale + (1 - ease) * t_scale;
}