#pragma once

typedef CEngineUI* (*CreateObjectFn)();

typedef FPMap* (*GetFPMapFn)();
typedef UIPMap* (*GetUIPMapFn)();

typedef void (*SetFPMapFn)(CEngineUI* UI, FPMap* Map);
typedef void (*SetUIPMapFn)();

typedef void (*AddFloatElementsFn)(CEngineUI* UI, const String& Name, float* Element);
typedef void (*AddUnsignedIntElementsFn)();