#pragma once

// �t���[�����ƂɍX�V����N���X�͑S�ẴN���X���p������
class Task {

public:
    Task() = default;
    virtual ~Task() = default;
    virtual bool update()     = 0; //�Ԃ�l true=����I�� false=����ȏ�X�V�s�v

};
