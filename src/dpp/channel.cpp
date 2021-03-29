#include <dpp/discord.h>
#include <dpp/discordevents.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dpp {

channel::channel() :
	id(0),
	flags(0),
	guild_id(0),
	position(0),
	last_message_id(0),
	user_limit(0),
	rate_limit_per_user(0),
	owner_id(0),
	parent_id(0),
	last_pin_timestamp(0)
{
}

channel::~channel()
{
}

bool channel::is_text_channel() {
	return flags & dpp::c_text;
}

bool channel::is_dm() {
	return flags & dpp::c_dm;
}

bool channel::is_voice_channel() {
	return flags & dpp::c_voice;
}

bool channel::is_group_dm() {
	return (flags & (dpp::c_dm | dpp::c_group)) == (dpp::c_dm | dpp::c_group);
}

bool channel::is_category() {
	return flags & dpp::c_category;
}

bool channel::is_news_channel() {
	return flags & dpp::c_news;
}

bool channel::is_store_channel() {
	return flags & dpp::c_store;
}

void channel::fill_from_json(json* j) {
	this->id = SnowflakeNotNull(j, "id");
	this->guild_id = SnowflakeNotNull(j, "guild_id");
	this->position = Int16NotNull(j, "position");
	this->name = StringNotNull(j, "name");
	this->topic = StringNotNull(j, "topic");
	this->last_message_id = SnowflakeNotNull(j, "last_message_id");
	this->user_limit = Int32NotNull(j, "user_limit");
	this->rate_limit_per_user = Int16NotNull(j, "rate_limit_per_user");
	this->owner_id = SnowflakeNotNull(j, "owner_id");
	this->parent_id = SnowflakeNotNull(j, "parent_id");
	//this->last_pin_timestamp
	uint8_t type = Int8NotNull(j, "type");
	this->flags |= BoolNotNull(j, "nsfw") ? dpp::c_nsfw : 0;
	this->flags |= (type == GUILD_TEXT) ? dpp::c_text : 0;
	this->flags |= (type == GUILD_VOICE) ? dpp::c_voice : 0;
	this->flags |= (type == DM) ? dpp::c_dm : 0;
	this->flags |= (type == GROUP_DM) ? (dpp::c_group | dpp::c_dm) : 0;
	this->flags |= (type == GUILD_CATEGORY) ? dpp::c_category : 0;
	this->flags |= (type == GUILD_NEWS) ? dpp::c_news : 0;
	this->flags |= (type == GUILD_STORE) ? dpp::c_store : 0;
}

};
