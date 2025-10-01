/*
 * Copyright (C) 2020, Inria
 * GRAPHDECO research group, https://team.inria.fr/graphdeco
 * All rights reserved.
 *
 * This software is free for non-commercial, research and evaluation use 
 * under the terms of the LICENSE.md file.
 *
 * For inquiries contact sibr@inria.fr and/or George.Drettakis@inria.fr
 */

#pragma once

#include "core/scene/IProxyMesh.hpp"

namespace sibr {
/**
	\ingroup sibr_scene
	*/
class SIBR_SCENE_EXPORT ProxyMesh : public IProxyMesh {
    SIBR_DISALLOW_COPY(ProxyMesh);

public:
    typedef std::shared_ptr<ProxyMesh> Ptr;

    ProxyMesh(){};
    ~ProxyMesh(){};
    void loadFromData(const IParseData::Ptr &data) override;
    void replaceProxy(Mesh::Ptr newProxy) override;
    void replaceProxyPtr(Mesh::Ptr newProxy) override;
    bool hasProxy(void) const override;
    const Mesh &proxy(void) const override;
    const Mesh::Ptr proxyPtr(void) const override;

protected:
    Mesh::Ptr _proxy;
};

inline bool sibr::ProxyMesh::hasProxy(void) const {
    return _proxy && !_proxy->vertices().empty();
}

inline const Mesh &ProxyMesh::proxy(void) const {
    return *_proxy;
}

inline const Mesh::Ptr ProxyMesh::proxyPtr(void) const {
    return _proxy;
}

};  // namespace sibr
