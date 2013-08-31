//
//  Adaptor1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/31/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Adaptor1__
#define __TestPattens__Adaptor1__

#include <iostream>
#include <vector>

namespace Adaptor1 {
    
    class Info{
    public:
        Info(const std::string& name) : mName(name){}
        virtual ~Info(){}
        
        const std::string& name() const {return mName;}
    private:
        std::string mName;
    };
    
    class IControlHander{
    public:
        virtual ~IControlHander(){}
    };
    
    class IControlAdaptation{
        
    public:
        virtual void onVisibilityChanged() {}
        virtual void onEnabledChanged() {}
        virtual void onInfoChanged() {}
    };
    
    class Control{
        typedef std::vector<IControlAdaptation*> Adaptations;
    public:
        Control() : mEnabled(true), mVisible(true), mInfo(nullptr), mHandler(nullptr){}
        virtual ~Control(){}
        
    public:
        
        void addAdaptation(IControlAdaptation* pAdaptation){
            mAdaptations.push_back(pAdaptation);
        }
        
        void removeAdaptation(IControlAdaptation* pAdaptation){
            auto it = std::find(mAdaptations.begin(), mAdaptations.end(), pAdaptation);
            if(it != mAdaptations.end()){
                mAdaptations.erase(it);
            }
        }
        
        IControlHander* handler() const {return mHandler;}
        void handler(IControlHander* pHandler){ mHandler = pHandler;}
        
        bool enabled() const {return mEnabled;}
        void enable(bool e){
            mEnabled = e;
            std::for_each(mAdaptations.begin(), mAdaptations.end(), [&](IControlAdaptation* pAdaptation){
                pAdaptation->onEnabledChanged();
            });
        }
        
        bool visible() const{return mVisible;}
        void visible(bool v){
            mVisible = v;
            std::for_each(mAdaptations.begin(), mAdaptations.end(), [&](IControlAdaptation* pAdaptation){
                pAdaptation->onVisibilityChanged();
            });
        }
        
        const Info* info(){return mInfo;}
        void info(Info* info) {mInfo = info;}
        
    private:
        Info* mInfo;
        bool mEnabled;
        bool mVisible;
        
        Adaptations mAdaptations;
        IControlHander* mHandler;
    };
    
    class IButtonHandler : public IControlHander{
    public:
        virtual void onClicked(){ std::cout << "IButtonHandler::setVisible " << std::endl;}
    };
    
    class IButtonAdaptation : public IControlAdaptation{

    };
    
    class Button : public Control{
    
    public:
        virtual void clicked(){ // notify hanlder.
            std::cout << "Button::clicked \n";
            if (IControlHander* pHandler = this->handler()) {
                if (IButtonHandler* btnHandler = dynamic_cast<IButtonHandler*>(pHandler)) {
                    btnHandler->onClicked();
                }
            }
        }
    };
    
    class CommandDef : public IButtonHandler{
      
    public:
        virtual Control* onControl() {
            Button* btn = new Button;
            btn->handler(this);
            return btn;
        }
        
        virtual void onClicked(){std::cout << "CommandDef::onClicked " << std::endl;}
    };
        
    
    class QButton{
    public:
        virtual void onClickedQ(){}
        void setVisible(bool b){ std::cout << "QButton::setVisible " << b << std::endl;}
        void setEnable(bool b) { std::cout << "QButton::setEnable " << b << std::endl;}
    };

    // Adapter
    class QTButton : public IButtonAdaptation,
                     public QButton
    {
    public:
        QTButton(Button* pLogicControl)
        : mLogicControl(pLogicControl)
        {
            pLogicControl->addAdaptation(this);
        }
        virtual ~QTButton(){
            mLogicControl->removeAdaptation(this);
        }
    
    public:
        // Trigged by real Control, then triger virtual control
        virtual void onClickedQ(){ mLogicControl->clicked();}

    protected:
        virtual void onEnabledChanged(){ this->setEnable(true);}
        virtual void onVisibilityChanged(){ this->setVisible(true);}

    private:
        Button* mLogicControl;
    };

    class QTMenuItem : public IButtonAdaptation,
                        public QButton
    {
    public:
        QTMenuItem(Button* pLogicControl)
        : mLogicControl(pLogicControl)
        {
            pLogicControl->addAdaptation(this);
        }
        virtual ~QTMenuItem(){
            mLogicControl->removeAdaptation(this);
        }
        
    public:
        // Trigged by real Control, then triger virtual control
        virtual void onClickedQ(){ mLogicControl->clicked();}
        
    protected:
        virtual void onEnabledChanged(){ this->setEnable(true);}
        virtual void onVisibilityChanged(){ this->setVisible(true);}
        
    private:
        Button* mLogicControl;
    };


    class Client{
    public:
        void run(){
            Info info1("AddTower");
            
            CommandDef cmd1;
            Button* btn1 = (Button*)cmd1.onControl();
            btn1->info(&info1);
            
            QTButton qbtn1(btn1);
            QTMenuItem qItem1(btn1);
            
            qbtn1.onClickedQ();
            
            btn1->enable(true);
            btn1->visible(false);
        }
    };


}

#endif /* defined(__TestPattens__Adaptor1__) */
