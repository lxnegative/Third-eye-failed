#include "opencv2\\opencv.hpp"
#include <tchar.h>
#include <vector>
#include <iostream>

using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
    
    //デフォルトの学習器
    //HOGDescriptor hog;// = HOGDescriptor(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
    //分類器の取得
    //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    //カスケードファイル（学習データが入っている）
    std::string nested_cascadeName = "haarcascade_fullbody.xml";

    //学習機の読み込み
    CascadeClassifier nested_cascade(nested_cascadeName.c_str());
    
    std::vector<cv::Rect> found;

    found.clear();
    

    //cv::VideoCapture cap(1);//デバイスのオープン   カメラがつながっている場合
                            //cap.open(0);//こっちでも良い．

    cv::VideoCapture cap("768x576.avi");

    if (!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
    {
        //読み込みに失敗したときの処理
        return -1;
    }

    //人の認識処理を行うタイミング　20なら20フレームごとに行う
    int interval = 0;
    int cnt = interval;

    

    while (1)//無限ループ
    {

        cv::Mat frame;
        //動画から画像の取得　（カメラから画像を取得）
        cap >> frame; // get a new frame from camera
        
        //失敗したら終了
        if (frame.empty()) {
            break;
        }
                      //
                      //取得したフレーム画像に対して，クレースケール変換や2値化などの処理を書き込む．
                      //

        if (cnt >= interval) {
            //HOG　デフォルトの学習機の場合
            //hog.detectMultiScale(frame, found, 0.3, Size(4, 4), Size(0, 0), 1.05, 2);
            //nested_cascade.detectMultiScale(frame, found, 1.11 , 3, CASCADE_SCALE_IMAGE, Size(10,10));
            
            //画像をグレースケールに変換
            cv::Mat gray_img;
            cvtColor(frame, gray_img, CV_BGR2GRAY);
            equalizeHist(gray_img, gray_img);

            //人の検出を行う　foundに検出した人の位置（x,y,width,height）が入る
            nested_cascade.detectMultiScale(gray_img, found);

            //グレースケール変換を行わない場合
            //nested_cascade.detectMultiScale(frame, found);

        }


        std::vector<cv::Rect>::const_iterator it;
        for (it = found.begin(); it != found.end(); ++it)
        {
            Rect r = *it;
            //人の位置に四角を書く
            rectangle(frame, r.tl(), r.br(), Scalar(255, 0, 0), 2);
        }

        namedWindow("window", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
        cv::imshow("window", frame);//画像を表示．

        int key = cv::waitKey(1);
        if (key == 113)//qボタンが押されたとき
        {
            break;//whileループから抜ける．
        }
        else if (key == 115)//sが押されたとき
        {
            //フレーム画像を保存する．
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
    //分類器の取得
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

    // 結果の描画
    namedWindow("hog", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    imshow("hog", img);
    waitKey(0);
    */

    return 0;
}