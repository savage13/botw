#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
}

namespace ksys::phys {

struct ActorInfo;
class BodyGroup;
struct StaticCompoundInfo;

class StaticCompound : public res::Resource, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(StaticCompound, res::Resource)

public:
    StaticCompound();
    ~StaticCompound() override;

    int setMapObject(u32 hash_id, u32 srt_hash, map::Object* object);
    map::Object* getMapObject(int shape_idx) const;

    bool disableCollision(int actor_idx, bool x);

    BodyGroup* getFieldBodyGroup(int idx);
    bool hasFieldBodyGroup(BodyGroup* group) const;

    // res::Resource interface
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* parent_heap) override;
    bool needsParse() const override { return true; }
    bool finishParsing_() override;
    bool m7_() override;

    void cleanUp();
    bool calledFromMapDtor();
    int getNumFieldBodyGroups() const { return mFieldBodyGroups.size(); }
    bool x_3();
    void x_4();
    StaticCompound* sub_7100FCAD0C(sead::Matrix34f& mtx);

private:
    enum class Flag {
        Initialised = 1 << 0,
    };

    sead::TypedBitFlag<Flag> mFlags;
    sead::Heap* mHeap{};
    const StaticCompoundInfo* mStaticCompoundInfo{};
    void* mBuffer{};
    int mBufferSize{};
    void* mContainerBuffer{};
    int mContainerBufferSize{};
    sead::Buffer<BodyGroup> mFieldBodyGroups;
    sead::FixedSafeString<32> mName;
    sead::Matrix34f mMtx = sead::Matrix34f::ident;
    sead::Buffer<map::Object*> mMapObjects{};
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(StaticCompound, 0x140);

}  // namespace ksys::phys
