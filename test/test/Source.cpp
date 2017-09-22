#include "opencv2\\opencv.hpp"
#include <tchar.h>
#include <vector>
#include <iostream>

using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
    
    //�f�t�H���g�̊w�K��
    //HOGDescriptor hog;// = HOGDescriptor(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
    //���ފ�̎擾
    //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    //�J�X�P�[�h�t�@�C���i�w�K�f�[�^�������Ă���j
    std::string nested_cascadeName = "haarcascade_fullbody.xml";

    //�w�K�@�̓ǂݍ���
    CascadeClassifier nested_cascade(nested_cascadeName.c_str());
    
    std::vector<cv::Rect> found;

    found.clear();
    

    //cv::VideoCapture cap(1);//�f�o�C�X�̃I�[�v��   �J�������Ȃ����Ă���ꍇ
                            //cap.open(0);//�������ł��ǂ��D

    cv::VideoCapture cap("768x576.avi");

    if (!cap.isOpened())//�J�����f�o�C�X������ɃI�[�v���������m�F�D
    {
        //�ǂݍ��݂Ɏ��s�����Ƃ��̏���
        return -1;
    }

    //�l�̔F���������s���^�C�~���O�@20�Ȃ�20�t���[�����Ƃɍs��
    int interval = 0;
    int cnt = interval;

    

    while (1)//�������[�v
    {

        cv::Mat frame;
        //���悩��摜�̎擾�@�i�J��������摜���擾�j
        cap >> frame; // get a new frame from camera
        
        //���s������I��
        if (frame.empty()) {
            break;
        }
                      //
                      //�擾�����t���[���摜�ɑ΂��āC�N���[�X�P�[���ϊ���2�l���Ȃǂ̏������������ށD
                      //

        if (cnt >= interval) {
            //HOG�@�f�t�H���g�̊w�K�@�̏ꍇ
            //hog.detectMultiScale(frame, found, 0.3, Size(4, 4), Size(0, 0), 1.05, 2);
            //nested_cascade.detectMultiScale(frame, found, 1.11 , 3, CASCADE_SCALE_IMAGE, Size(10,10));
            
            //�摜���O���[�X�P�[���ɕϊ�
            cv::Mat gray_img;
            cvtColor(frame, gray_img, CV_BGR2GRAY);
            equalizeHist(gray_img, gray_img);

            //�l�̌��o���s���@found�Ɍ��o�����l�̈ʒu�ix,y,width,height�j������
            nested_cascade.detectMultiScale(gray_img, found);

            //�O���[�X�P�[���ϊ����s��Ȃ��ꍇ
            //nested_cascade.detectMultiScale(frame, found);

        }


        std::vector<cv::Rect>::const_iterator it;
        for (it = found.begin(); it != found.end(); ++it)
        {
            Rect r = *it;
            //�l�̈ʒu�Ɏl�p������
            rectangle(frame, r.tl(), r.br(), Scalar(255, 0, 0), 2);
        }

        namedWindow("window", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
        cv::imshow("window", frame);//�摜��\���D

        int key = cv::waitKey(1);
        if (key == 113)//q�{�^���������ꂽ�Ƃ�
        {
            break;//while���[�v���甲����D
        }
        else if (key == 115)//s�������ꂽ�Ƃ�
        {
            //�t���[���摜��ۑ�����D
            cv::imwrite("img.png", frame);
        }

        cnt++;
        if (cnt > interval) {
            cnt = 0;
        }

    }

    cv::destroyAllWindows();
    return 0;
    
    
    /*
    Mat img = imread("img.png", 1);

    HOGDescriptor hog = HOGDescriptor(Size(48, 96), Size(16, 16),Size(8,8),Size(8,8),9);
    //���ފ�̎擾
    hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
    
    std::vector<cv::Rect> found;
    //HOG
    hog.detectMultiScale(img, found, 0.6, Size(4, 4), Size(0, 0), 1.05,2);

    std::vector<cv::Rect>::const_iterator it;
    for (it = found.begin(); it != found.end(); ++it)
    {
        Rect r = *it;
        rectangle(img, r.tl(), r.br(), Scalar(255, 0, 0), 2);
    }

    // ���ʂ̕`��
    namedWindow("hog", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    imshow("hog", img);
    waitKey(0);
    */

    return 0;
}