/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */

#include "nsTreeTwistyListener.h"
#include "nsIDOMEventReceiver.h"
#include "nsIDOMEventListener.h"

#include "nsCOMPtr.h"
#include "nsIDOMUIEvent.h"
#include "nsIPresContext.h"
#include "nsIContent.h"
#include "nsIDOMNode.h"
#include "nsIDOMElement.h"
#include "nsXULAtoms.h"
#include "nsIDOMEventListener.h"

/*
 * nsTreeTwistyListener implementation
 */

NS_IMPL_ADDREF(nsTreeTwistyListener)
NS_IMPL_RELEASE(nsTreeTwistyListener)
NS_IMPL_QUERY_INTERFACE1(nsTreeTwistyListener, nsIDOMMouseListener)

////////////////////////////////////////////////////////////////////////


nsTreeTwistyListener::nsTreeTwistyListener()
{
  NS_INIT_REFCNT();
}

////////////////////////////////////////////////////////////////////////
nsTreeTwistyListener::~nsTreeTwistyListener() 
{
}


////////////////////////////////////////////////////////////////////////

static void GetTreeItem(nsIDOMElement* aElement, nsIDOMElement** aResult)
{
  nsCOMPtr<nsIContent> content = do_QueryInterface(aElement);
  while (content) {
    nsCOMPtr<nsIAtom> tag;
    content->GetTag(*getter_AddRefs(tag));
    if (tag.get() == nsXULAtoms::treeitem) {
      nsCOMPtr<nsIDOMElement> result = do_QueryInterface(content);
      *aResult = result.get();
      NS_IF_ADDREF(*aResult);
      return;
    }

    nsCOMPtr<nsIContent> parent;
    content->GetParent(*getter_AddRefs(parent));
    content = parent;
  }
}

nsresult
nsTreeTwistyListener::MouseDown(nsIDOMEvent* aEvent)
{  
  // Get the target of the event. If it's a titledbutton, we care.
  nsCOMPtr<nsIDOMEventTarget> target;
  aEvent->GetTarget(getter_AddRefs(target));

  nsCOMPtr<nsIDOMElement> element = do_QueryInterface(target);
  if (!element)
    return NS_OK;

  // Find out if we're the twisty.
  nsAutoString twistyAttr;
  element->GetAttribute(NS_ConvertASCIItoUCS2("twisty"), twistyAttr);
  if (twistyAttr.EqualsWithConversion("true")) {
    // Retrieve the parent treeitem.
    nsCOMPtr<nsIDOMElement> treeItem;
    GetTreeItem(element, getter_AddRefs(treeItem));

    if (!treeItem)
      return NS_OK;

    nsAutoString empty;
    treeItem->GetAttribute(NS_ConvertASCIItoUCS2("empty"), empty);
    if (empty.EqualsWithConversion("true"))
      return NS_OK;

    // Eat the event.
    aEvent->PreventCapture();
    aEvent->PreventBubble();
    aEvent->PreventDefault();

    nsAutoString open;
    treeItem->GetAttribute(NS_ConvertASCIItoUCS2("open"), open);
    if (open.EqualsWithConversion("true"))
      treeItem->RemoveAttribute(NS_ConvertASCIItoUCS2("open"));
    else treeItem->SetAttribute(NS_ConvertASCIItoUCS2("open"), NS_ConvertASCIItoUCS2("true"));
  }
  return NS_OK;
}
