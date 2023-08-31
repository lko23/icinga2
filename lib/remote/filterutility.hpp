/* Icinga 2 | (c) 2012 Icinga GmbH | GPLv2+ */

#ifndef FILTERUTILITY_H
#define FILTERUTILITY_H

#include "remote/i2-remote.hpp"
#include "remote/apiuser.hpp"
#include "config/expression.hpp"
#include "base/dictionary.hpp"
#include "base/configobject.hpp"
#include <set>
#include <utility>

namespace icinga
{

class TargetProvider : public Object
{
public:
	DECLARE_PTR_TYPEDEFS(TargetProvider);

	virtual void FindTargets(const String& type, const std::function<void (const Value&)>& addTarget) const = 0;
	virtual Value GetTargetByName(const String& type, const String& name) const = 0;
	virtual bool IsValidType(const String& type) const = 0;
	virtual String GetPluralName(const String& type) const = 0;
};

class ConfigObjectTargetProvider final : public TargetProvider
{
public:
	DECLARE_PTR_TYPEDEFS(ConfigObjectTargetProvider);

	void FindTargets(const String& type, const std::function<void (const Value&)>& addTarget) const override;
	Value GetTargetByName(const String& type, const String& name) const override;
	bool IsValidType(const String& type) const override;
	String GetPluralName(const String& type) const override;
};

struct QueryDescription
{
	std::set<String> Types;
	TargetProvider::Ptr Provider;
	String Permission;
};

/**
 * Filter utilities.
 *
 * @ingroup remote
 */
class FilterUtility
{
public:
	static Type::Ptr TypeFromPluralName(const String& pluralName);
	static void CheckPermission(const ApiUser::Ptr& user, const String& permission, std::unique_ptr<Expression>* filter = nullptr);
	static bool HasPermission(const ApiUser::Ptr& user, const String& permission, std::unique_ptr<Expression>* permissionFilter = nullptr);
	static std::vector<Value> GetFilterTargets(const QueryDescription& qd, const Dictionary::Ptr& query,
		const ApiUser::Ptr& user, const String& variableName = String());
	static bool EvaluateFilter(ScriptFrame& frame, Expression *filter,
		const Object::Ptr& target, const String& variableName = String());

private:
	static bool GetTargetServices(Expression* filter, const Dictionary::Ptr& constants, std::vector<std::pair<const String *, const String *>>& out);
	static std::pair<const String *, const String *> GetTargetService(Expression* filter, const Dictionary::Ptr& constants);
	static bool GetTargetHosts(Expression* filter, const Dictionary::Ptr& constants, std::vector<const String *>& out);
	static const String * GetComparedName(Expression* filter, const char * lcType, const Dictionary::Ptr& constants);
	static bool IsNameIndexer(Expression* exp, const char * lcType, const Dictionary::Ptr& constants);
	static const String * GetConstString(Expression* exp, const Dictionary::Ptr& constants);
	static const Value * GetConst(Expression* exp, const Dictionary::Ptr& constants);
};

}

#endif /* FILTERUTILITY_H */
