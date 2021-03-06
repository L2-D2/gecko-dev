/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "WebGL2Context.h"
#include "GLContext.h"

using namespace mozilla;
using namespace mozilla::dom;

// -------------------------------------------------------------------------
// Query Objects
// TODO(djg): Implemented in WebGLContext

/*
    already_AddRefed<WebGLQuery> CreateQuery();
    void DeleteQuery(WebGLQuery* query);
    bool IsQuery(WebGLQuery* query);
    void BeginQuery(GLenum target, WebGLQuery* query);
    void EndQuery(GLenum target);
    JS::Value GetQuery(JSContext*, GLenum target, GLenum pname);
*/
void
WebGL2Context::GetQueryParameter(JSContext*, WebGLQuery* query, GLenum pname, JS::MutableHandleValue retval)
{
    MOZ_CRASH("Not Implemented");
}
