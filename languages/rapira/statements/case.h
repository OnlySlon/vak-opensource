#ifndef CASE_H
#define CASE_H

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

#include "../nodelist.h"
#include "../primitives/logical.h"
#include "../operations/equal.h"
#include "../exceptions/invalidtype.h"

class Case : public Node
{

	public:

		/*** Constructor ***/
		Case();

		/*** Set the case condition ***/
		void setCondition(Object* expr);

		/*** Add a when ***/
		void addWhen(Object* expr, NodeList* list);

		/*** Add an else ***/
		void setElse(NodeList* list);

		/*** Execute this node ***/
		Outcome execute();

		/*** Clone this object ***/
		Case* clone() const
		{
			Case* ncn = new Case();
			ncn->setLineNumber(getLineNumber());
			ncn->setColumnNumber(getColumnNumber());
			if(condition != 0)
				ncn->setCondition(condition->clone());
			if(elseStmts != 0)
				ncn->setElse(elseStmts->clone());
			for(unsigned int i = 0; i < whenStmts.size(); i++)
				ncn->addWhen(whenStmts.at(i).first->clone(), whenStmts.at(i).second->clone());
			return ncn;
		}

		/*** Destructor ***/
		~Case();

	private:

		/*** The case condition ***/
		Object* condition;

		/*** The vector of condition, NodeList pairs ***/
		std::vector< std::pair<Object*, NodeList* > > whenStmts;

		/*** The else NodeList ***/
		NodeList* elseStmts;
};

#endif
