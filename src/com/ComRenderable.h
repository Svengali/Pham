//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

#include "./Component.h"

#include "../grx/Geometry.h"


namespace com
{

class ComRenderableConfig : public ComponentCfg
{
public:
    CLASS(ComRenderableConfig, ComponentCfg);

    virtual void DoReflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
    REFLECT_BEGIN(ComRenderableConfig, ComponentCfg);
        REFLECT(m_geo);
    REFLECT_END();

    GeometryPtr m_geo;

    //virtual Component<ComRenderableConfig>* CreateCom(ent::Entity* const pEnt);
};

PtrDef(ComRenderableConfig);


class ComRenderable : public Component<ComRenderableConfig>
{

public:
    CLASS(ComRenderable, Component);

    ComRenderable( ent::EntityBase* const pEnt = NULL, const ComRenderableConfigPtr& config = ComRenderableConfigPtr(NULL));

    virtual ~ComRenderable();

    void Render(RenderContext *pRC, const cb::Frame3& frame);

    REFLECT_BEGIN(ComRenderable, Component);
    REFLECT_END();

private:
};


PtrDef(ComRenderable);


}
