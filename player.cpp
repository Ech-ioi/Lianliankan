#include "player.h"
#include<iostream>


void Player::play()
{
    backsound=new QSound("F:/Lianliankan/music/background.wav");
    backsound->setLoops(-1);//无限循环
    backsound->play();

}
void Player::stop(){
    std::cout<<"stop"<<std::endl;
    backsound->stop();
//    delete backsound;
}

Player::~Player(){
    std::cout<<"player::~player"<<std::endl;
    backsound->stop();
    delete backsound;
    delete sound1;
    delete sound2;
}

void Player::play1(){
    std::cout<<"play1"<<std::endl;
    sound1=new QSound("F:/Lianliankan/music/select.wav");
    sound1->play();
}
void Player::play2(){
    std::cout<<"play2"<<std::endl;
    sound2=new QSound("F:/Lianliankan/music/pair.wav");
    sound2->play();
}
void Player::stop1(){
    std::cout<<"stop1"<<std::endl;
    sound1=new QSound("F:/Lianliankan/music/select.wav");
    sound1->stop();
}
void Player::stop2(){
    std::cout<<"stop2"<<std::endl;
    sound2=new QSound("F:/Lianliankan/music/pair.wav");
    sound2->stop();
}
