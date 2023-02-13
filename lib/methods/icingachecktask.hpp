/* Icinga 2 | (c) 2023 Icinga GmbH | GPLv2+ */

#pragma once

#include "methods/i2-methods.hpp"
#include "icinga/service.hpp"

namespace icinga
{

/**
 * Icinga check type.
 *
 * @ingroup methods
 */
class IcingaCheckTask
{
public:
	static void ScriptFunc(const Checkable::Ptr& checkable, const CheckResult::Ptr& cr,
		const Dictionary::Ptr& resolvedMacros, bool useResolvedMacros);

private:
	IcingaCheckTask();
};

}
