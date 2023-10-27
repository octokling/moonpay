#include "lib.hpp"
#include "patches.hpp"
#include "nn/err.h"
#include "nn/account.h"
#include "logger/Logger.hpp"
#include "fs.h"
#include "rs/util.hpp"

#include <basis/seadRawPrint.h>
#include <prim/seadSafeString.h>
#include <resource/seadResourceMgr.h>
#include <filedevice/nin/seadNinSDFileDeviceNin.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <resource/seadArchiveRes.h>
#include <framework/seadFramework.h>
#include <heap/seadHeapMgr.h>
#include <heap/seadExpHeap.h>
#include <devenv/seadDebugFontMgrNvn.h>
#include <gfx/seadTextWriter.h>
#include <gfx/seadViewport.h>

#include "al/util.hpp"
#include "game/StageScene/StageScene.h"
#include "game/System/GameSystem.h"
#include "game/System/Application.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "rs/util.hpp"
#include "al/fs/FileLoader.h"

#include "agl/utl.h"
#include "al/resource/Resource.h"

#include "game/Actors/Shine.h"
#include "game/GameData/GameDataFunction.h"
#include "game/GameData/GameDataFile.h"
#include "game/Actors/CoinCollect.h"

#include "CapMessageShowInfo.h"
#include "CapMessageDirectorFunction.h"
#include "CapMessageLayout.h"
#include "CapMessageDirector.h"

#include "helps/tryGets.h"

#include "ExceptionHandler.h"
#include "al/layout/WindowConfirmWait.h"

#include "layouts/ShineCost/ShineCostLayout.h"
#include "Events/Event.h"

//paramètres


/*static const char *DBG_FONT_PATH   = "DebugData/Font/nvn_font_jis1.ntx";
static const char *DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char *DBG_TBL_PATH    = "DebugData/Font/nvn_font_jis1_tbl.bin";*/

sead::TextWriter *gTextWriter;

int shineCost = 15;
int needPay = 0;
int lastPayedMoonId = 0;

ShineCostLayout* mShineConstLayout = nullptr;
Event* PayToMoonEvent = nullptr;
bool requirementToBeginEvent = false;

bool shineHasAppearAnimation = false;

bool isInSnapShot = false;

HOOK_DEFINE_TRAMPOLINE(GameSystemInit) {
    static void Callback(GameSystem *thisPtr) {

        /*sead::Heap* curHeap = sead::HeapMgr::instance()->getCurrentHeap();

        sead::DebugFontMgrJis1Nvn::createInstance(curHeap);

        if (al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_TBL_PATH)) {
            sead::DebugFontMgrJis1Nvn::sInstance->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH, 0x100000);
        }
        sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::sInstance);

        al::GameDrawInfo* drawInfo = Application::instance()->mDrawInfo;

        agl::DrawContext *context = drawInfo->mDrawContext;
        agl::RenderBuffer* renderBuffer = drawInfo->mFirstRenderBuffer;

        sead::Viewport* viewport = new sead::Viewport(*renderBuffer);

        gTextWriter = new sead::TextWriter(context, viewport);

        gTextWriter->setupGraphics(context);

        gTextWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);*/
        

        nn::account::Uid uid;
        nn::account::GetLastOpenedUser(&uid);

            char uidString[37];
            sprintf(uidString, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                uid.data[0], uid.data[1], uid.data[2], uid.data[3], uid.data[4], uid.data[5], uid.data[6], uid.data[7],
                uid.data[8], uid.data[9], uid.data[10], uid.data[11], uid.data[12], uid.data[13], uid.data[14], uid.data[15]);

            if (strcmp(uidString, "B43B157C-6D2C-0010-8D1D-A75831B0103F") == 0 || strcmp(uidString, "8CF01792-697C-D9C1-4FF2-6AA6BD4DFBA4") == 0 || strcmp(uidString, "11D96C7A-2A5A-E768-9AE7-94528F27150E") == 0 || strcmp(uidString, "6E8EB95D-8B39-6D8B-585A-D922447BB13D") == 0 || strcmp(uidString, "4F47A8CD-D216-4101-1D3B-3E363935B8F") == 0 || strcmp(uidString, "A3662F19-C35E-C743-4AF7-E8E439CADE9F") == 0 || strcmp(uidString, "7D87D153-0000-0010-8259-F7131041FCC4") == 0 || strcmp(uidString, "6FEDD586-EC15-803F-4F64-E706F293BE36") == 0 || strcmp(uidString, "D67E020A-6D15-0010-9C45-978F4445E74D") == 0 || strcmp(uidString, "02EFB940-29E8-D897-515D-937ABF727B1B") == 0 || strcmp(uidString, "336502FB-FCD5-092F-F6A8-7D752D998495") == 0 || strcmp(uidString, "EFB20D50-CC16-EAFC-34F9-965D9E9EB957") == 0 || strcmp(uidString, "3184792C-828A-8EC8-7970-6B2E37E957DB") == 0) {
                Logger::log("Beta tester autorisée\n");
            } else {
                Logger::log("Beta tester non autorisée\n");
                nn::err::ApplicationErrorArg obj;
                obj.SetApplicationErrorCodeNumber(01);
                obj.SetDialogMessage("Erreur : Vous n'avez pas l'autorisation d'utiliser le mod !");
                obj.SetFullScreenMessage("D'après une vérification de la console, vous n'êtes pas autorisé à jouer à ce mod, veuillez désinstaller ce mod !\nVous pensez que cela est une erreur, veuillez en parler à Octokling.");
                obj.language_code = nn::settings::LanguageCode::Make(nn::settings::Language_French);
                nn::err::ShowApplicationError(obj);

                svcExitProcess();
            };
        
        Orig(thisPtr);

        

    }
};

/*HOOK_DEFINE_TRAMPOLINE(DrawDebugMenu) {
    static void Callback(HakoniwaSequence *thisPtr) { 

        Orig(thisPtr);

        gTextWriter->beginDraw();
        gTextWriter->setCursorFromTopLeft(sead::Vector2f(10.f, 10.f));
        gTextWriter->printf("shineCost : %i\n", shineCost);
        gTextWriter->printf("needPay: %i\n", needPay);
        gTextWriter->endDraw();

    }
};/**/

bool islaunchedCooldown = false;
int frameOfCooldown = 0;

const char* randomMessageAlreadyTaked(){
    int randomValue = al::getRandom(1, 250);
    if(randomValue == 26) return "SecretAlreadyTaked1";
    if(randomValue == 125) return "SecretAlreadyTaked2";
    if(randomValue <= 50) return "AlreadyTaked1";
    if(randomValue <= 100) return "AlreadyTaked2";
    if(randomValue <= 150) return "AlreadyTaked3";
    if(randomValue <= 200) return "AlreadyTaked4";
    if(randomValue <= 250) return "AlreadyTaked5";
}

const char* randomMessageNotEnouthMoney(){
    int randomValue = al::getRandom(1, 250);
    if(randomValue == 26) return "SecretNotEnouthMoney1";
    if(randomValue == 125) return "SecretNotEnouthMoney2";
    if(randomValue <= 50) return "NotEnouthMoney1";
    if(randomValue <= 100) return "NotEnouthMoney2";
    if(randomValue <= 150) return "NotEnouthMoney3";
    if(randomValue <= 200) return "NotEnouthMoney4";
    if(randomValue <= 250) return "NotEnouthMoney5";
}

void calculShineCost(StageScene* scene){
    int moon = GameDataFunction::getTotalShineNum(scene, -1);
    
    int cost = moon * shineCost;

    if(cost >= 9999) cost = 9999;
    if(PayToMoonEvent->getCurrentEventName() == "SHINECOST_MINISOLD"){
        cost  = cost / 1.1;
    }

    mShineConstLayout->updateCost(cost);
    needPay = cost;
}

void executeEvents(StageScene* scene){
    //Si mario à récupéré une Lune, alors le layout d'affiche
    if(needPay != 0){
        PlayerActorBase* playerActor = tryGetPlayerActor(scene);
        if(!scene->mSceneLayout->coinCounter->isWait()){ //Si le layout des pièces est en animation "Wait"
            mShineConstLayout->tryEnd();
        }else{
            mShineConstLayout->tryStart();
        }

        if(requirementToBeginEvent == true){
            PayToMoonEvent->tryStartCooldown();
        }else{
            if(playerActor){
                requirementToBeginEvent = GameDataFunction::isAlreadyGoWorld(playerActor, 2);
            }
        }
    }

    //Si Mario est aller pour la première fois à sandKingdom, alors les évenements sont activées
}

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene* scene) {
        Orig(scene);

        calculShineCost(scene);

        al::PlayerHolder* playerHolder = al::getScenePlayerHolder(scene);
        PlayerActorHakoniwa* playerActor = playerHolder->tryGetPlayer(0);

        if(!scene->isPause() && al::isAlive(playerActor)){ //Si le jeu n'est pas en pause et que l'acteur est en vie

            executeEvents(scene);

            if(!isInSnapShot){
                PayToMoonEvent->update();
            }else{
                isInSnapShot = false;
            }

            if(islaunchedCooldown){
                if(frameOfCooldown >= 300){
                    islaunchedCooldown = false;
                }else{
                    frameOfCooldown++;
                }
            }
        }
    }
};


HOOK_DEFINE_TRAMPOLINE(ShineMsg) {
    static void Callback(Shine* shine, const al::SensorMsg *Sensor, al::HitSensor *HitSensor, al::HitSensor *HitSensor2) { 

        GameDataHolderAccessor* mHolder = tryGetGameDataHolderAccess();
        al::Scene* mScene = tryGetScene();
        int coin = GameDataFunction::getCoinNum(*mHolder);

        if(rs::isMsgShineGet(Sensor) || rs::isMsgShineGet2D(Sensor)){

            if(GameDataFunction::isGotShine(*mHolder, shine->shineId)){
                    
                if(islaunchedCooldown == false){
                    const char* message = randomMessageAlreadyTaked();
                    rs::showCapMessage(shine, message, 150, 20);
                    frameOfCooldown = 0;
                    islaunchedCooldown = true;
                }

                return;

            }else if(coin >= needPay){
                if(lastPayedMoonId != shine->shineId){
                    Logger::log("isEndAppear : %s\n", shine->isEndAppearGK() ? "True" : "False");
                    if(shine->isEndAppearGK() == true){
                        GameDataFunction::subCoin(*mHolder, needPay);
                        Logger::log("Shine payed\n");
                        Orig(shine, Sensor, HitSensor, HitSensor2);
                        lastPayedMoonId = shine->shineId;
                    }else{
                        return;
                    }
                }

            }else{
                if(islaunchedCooldown == false){
                    frameOfCooldown = 0;
                    islaunchedCooldown = true;
                    const char* message = randomMessageNotEnouthMoney();
                    //Logger::log(message);
                    rs::showCapMessage(shine, message, 150, 20);
                }
                return;
            }
        }
        Orig(shine, Sensor, HitSensor, HitSensor2);
    }
};


void initActorInitInfo(al::ActorInitInfo *info, StageScene *curScene, al::PlacementInfo const *placement, al::LayoutInitInfo const *lytInfo, al::ActorFactory const *factory, al::SceneMsgCtrl *sceneMsgCtrl, al::GameDataHolderBase *dataHolder){
    al::initActorInitInfo(info, curScene, placement, lytInfo, factory, sceneMsgCtrl, dataHolder);

    PayToMoonEvent = new Event(curScene);
    mShineConstLayout = new ShineCostLayout("ShineCost", *lytInfo);
    
    calculShineCost(curScene);
    //Logger::log("Stage Initied !\n");
}

HOOK_DEFINE_TRAMPOLINE(SnapShotExeWait){
    static void Callback(StageSceneStateSnapShot *thisptr){
        Orig(thisptr);
        isInSnapShot = true;
    }
};

//L'étoile de la boutique doit avoir le même prix que le prix du défi !




extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    //envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    handler::installExceptionHandler([](handler::ExceptionInfo& info) {
        handler::printCrashReport(info);
        return false;
    });

    if(LOGGER_IP != "0.0.0.0")
        Logger::instance().init(LOGGER_IP, 3080);

    runCodePatches();
    installHooks();

    GameSystemInit::InstallAtOffset(0x535850); //Very important part

    /*if(DEBUGMOD == "true"){
        // Debug Text Writer Drawing
        DrawDebugMenu::InstallAtOffset(0x50F1D8);   
    }*/

    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv"); //Les déplacements de Mario
    
    ShineMsg::InstallAtSymbol("_ZN5Shine10receiveMsgEPKN2al9SensorMsgEPNS0_9HitSensorES5_"); //Lorsque Shine est appelé par la fonction receiveMsg
    SnapShotExeWait::InstallAtSymbol("_ZN23StageSceneStateSnapShot7exeWaitEv");

    exl::patch::CodePatcher(0x4C8DD0).BranchLinkInst(reinterpret_cast<void*>(initActorInitInfo));

    //GreyShineRefreshHook::InstallAtSymbol("_ZN16GameDataFunction10isGotShineE22GameDataHolderAccessorPK9ShineInfo");
    //test::InstallAtSymbol("_ZN16GameDataFunction11isEnableCapE22GameDataHolderAccessor");
    //test::InstallAtSymbol("_ZN16CapMessageLayout9startCoreEPK18CapMessageShowInfob");//Ceci est un test seulement !

}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}