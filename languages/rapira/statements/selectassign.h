#ifndef SELECTASSIGN_H
#define SELECTASSIGN_H

// ReRap Version 0.9
// Copyright 2011 Matthew Mikolay.
//
// This file is part of ReRap.
//
// ReRap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ReRap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ReRap.  If not, see <http://www.gnu.org/licenses/>.

#include "../operations/select.h"
#include "assign.h"
#include "../primitives/integer.h"
#include "../primitives/sequence.h"
#include "../primitives/text.h"
#include "../exceptions/invalidtype.h"
#include "../exceptions/invalidindex.h"

class SelectAssign : public Node
{

	public:

		/*** Constructor ***/
		SelectAssign();

		/*** Constructor ***/
		SelectAssign(Variable* pTarget, Object* pIndex, Object* pExpr);

		/*** Set the target ***/
		void setTarget(Variable* pTarget);

		/*** Set the index ***/
		void setIndex(Object* pIndex);

		/*** Set the expression ***/
		void setExpression(Object* pExpr);

		/*** Execute this node ***/
		Outcome execute();

		/*** Clone this object ***/
		SelectAssign* clone() const
		{
			SelectAssign* nsn = new SelectAssign();
			nsn->setLineNumber(getLineNumber());
			nsn->setColumnNumber(getColumnNumber());
			if(target != 0)
				nsn->setTarget(target->clone());
			if(index != 0)
				nsn->setIndex(index->clone());
			if(expr != 0)
				nsn->setExpression(expr->clone());
			return nsn;
		}

		/*** Destructor ***/
		~SelectAssign();

	private:

		/*** The target ***/
		Variable* target;

		/*** The index ***/
		Object* index;

		/*** The expression ***/
		Object* expr;

};

#endif
