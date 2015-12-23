#include "stdio.h"

#include "orxPluginAPI.h"
#include "orx.h"

const char* kevin = "watters";

orxOBJECT* hero;
orxOBJECT* herosGun;

static orxVECTOR leftSpeed = {-20, 0, 0};
static orxVECTOR rightSpeed = {20, 0, 0};
static orxVECTOR jumpSpeed = {0, -600, 0};

static orxVECTOR flipLeft = { -2, 2, 1 };
static orxVECTOR flipRight = { 2, 2, 1 };

static void create_explosion(orxOBJECT* object, orxSTRING exploderName) {
  if (!object)
    return;

  orxVECTOR pos;
  orxObject_GetWorldPosition(object, &pos);
  pos.fZ = 0.0;

  orxOBJECT* explosion = orxObject_CreateFromConfig(exploderName);
  orxObject_SetPosition(explosion, &pos);
}


static orxSTATUS orxFASTCALL spud_physics(const orxEVENT* e) {
  if (e->eID == orxPHYSICS_EVENT_CONTACT_ADD) { // TODO: autocomplete
    orxOBJECT* sender = orxOBJECT(e->hSender);
    orxOBJECT* receiver = orxOBJECT(e->hRecipient);

    orxSTRING senderName = (orxSTRING)orxObject_GetName(sender);
    orxSTRING receiverName = (orxSTRING)orxObject_GetName(receiver);

    if (orxString_Compare(senderName, "StarObject") == 0) {
      orxObject_SetLifeTime(sender, 0);
    }
    if (orxString_Compare(receiverName, "StarObject") == 0) {
      orxObject_SetLifeTime(receiver, 0);
    }
    if (orxString_Compare(senderName, "BulletObject") == 0) {
      create_explosion(receiver, "JellyExploder");
      orxObject_SetLifeTime(sender, 0);
      orxObject_SetLifeTime(receiver, 0);
    }
    if (orxString_Compare(receiverName, "BulletObject") == 0) {
      create_explosion(sender, "JellyExploder");
      orxObject_SetLifeTime(sender, 0);
      orxObject_SetLifeTime(receiver, 0);
    }
  }

  return orxSTATUS_SUCCESS;
}

static void orxFASTCALL spud_update(const orxCLOCK_INFO* clockInfo, void* context) {
  if (orxInput_IsActive("Quit")) {
    orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
  }

  if (orxInput_IsActive("GoLeft")) {
    orxObject_SetScale(hero, &flipLeft);
    orxObject_ApplyImpulse(hero, &leftSpeed, orxNULL);
    orxObject_SetTargetAnim(hero, "HeroRun");
  } else if (orxInput_IsActive("GoRight")) {
    orxObject_SetScale(hero, &flipRight);
    orxObject_ApplyImpulse(hero, &rightSpeed, orxNULL);
    orxObject_SetTargetAnim(hero, "HeroRun");
  } else {
    orxObject_SetTargetAnim(hero, orxNULL);
  }

  orxObject_Enable(herosGun, orxInput_IsActive("Shoot"));

  if (orxInput_IsActive("Jump") && orxInput_HasNewStatus("Jump")) {
    orxObject_ApplyImpulse(hero, &jumpSpeed, orxNULL);
  }
}

static orxSTATUS spud_init() {
  orxSTATUS result = orxSTATUS_SUCCESS;
  orxViewport_CreateFromConfig("Viewport");

  hero = orxObject_CreateFromConfig("HeroObject");
  if (!hero) {
    orxLOG("Could not create HeroObject");
    return orxSTATUS_FAILURE;
  }
  herosGun = (orxOBJECT*)orxObject_GetChild(hero);
  if (!herosGun) {
    orxLOG("Could not get hero's gun");
    return orxSTATUS_FAILURE;
  }

  orxObject_Enable(herosGun, false);

  orxObject_CreateFromConfig("Scene");

  orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, spud_physics);

  // register an update clock
  orxCLOCK* clock = orxClock_FindFirst(orx2D(-1.0f), orxCLOCK_TYPE_CORE);
  result = orxClock_Register(clock, spud_update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_HIGH);
  if (result != orxSTATUS_SUCCESS) {
    orxLOG("could not register update clock");
    return result;
  }

  return result;
}

orxPLUGIN_DECLARE_ENTRY_POINT(spud_init);
