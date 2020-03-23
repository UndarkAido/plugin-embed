#pragma once

#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <nlohmann/json.hpp>

namespace discordpp{

	/**
	 * @class MessageEmbed
	 * @details Anything denoted as "optional" can have a nullptr as input
	 */

	class MessageEmbed{
	public:

		/**
		 * @param title
		 * @details Sets embed title.
		 * @returns MessageEmbed
		 */

		MessageEmbed setTitle(const std::string& title){
			embed["title"] = title;

			return *this;
		}

		/**
		 * @param desc
		 * @details Sets embed description
		 * @returns MessageEmbed
		 */

		MessageEmbed setDescription(const std::string& desc){
			embed["description"] = desc;

			return *this;
		}

		/**
		 * @param color
		 * @details Sets embed color
		 * @returns MessageEmbed
		 */

		MessageEmbed setColor(const int color){
			embed["color"] = color;

			return *this;
		}

		/**
		 * @param url
		 * @details Sets embed url for title
		 * @returns MessageEmbed
		 */

		MessageEmbed setURL(const std::string& url){
			embed["url"] = url;

			return *this;
		}

		/**
		 * @param footText
		 * @details Sets footer text for embed
		 * @returns MessageEmbed
		 */

		MessageEmbed setFooterText(const std::string& footText){
			embed["footer"]["text"] = footText;

			return *this;
		}

		/**
		 * @param footIconURL
		 * @details Sets footer icon for embed
		 * @returns MessageEmbed
		 */

		MessageEmbed setFooterIconURL(const std::string& footIconURL){
			embed["footer"]["icon_url"] = footIconURL;

			return *this;
		}

		/**
		 * @param title
		 * @param desc
		 * @param _inline
		 * @details Adds new fields to embed. desc is optional.
		 * @returns MessageEmbed
		 */

		MessageEmbed addField(std::string title, std::string desc, bool _inline){
			if(embed.find("fields") == embed.end()) embed["fields"] = nlohmann::json::array();

			nlohmann::json toPush;

			toPush["name"] = title;
			toPush["value"] = desc;
			toPush["inline"] = _inline;

			embed["fields"].push_back(toPush);

			return *this;
		}

		/**
		 * @param url
		 * @details Sets image url for embed. Not compatible with MessageEmbed#setThumbnail
		 * @returns MessageEmbed
		 */

		MessageEmbed setImage(const std::string& url){
			embed["image"]["url"] = url;

			return *this;
		}

		/**
		 * @param url
		 * @details Sets thumbnail url for embed. Not compatible with MessageEmbed#setImage
		 * @returns MessageEmbed
		 */

		MessageEmbed setThumbnail(const std::string& url){
			embed["thumbnail"]["url"] = url;

			return *this;
		}

		/**
		 * @param name
		 * @param iconURL
		 * @details Sets author name and icon. iconURL is optional.
		 * @returns MessageEmbed
		 */

		MessageEmbed setAuthor(const std::string& name, const std::string& iconURL){
			embed["author"]["name"] = name;
			embed["author"]["icon_url"] = iconURL;

			return *this;
		}

		/**
		 * @param timestamp
		 * @details Sets ISO 8061 Timestamp. timestamp is optional and will default to now.
		 * @returns MessageEmbed
		 */
		MessageEmbed setTimestamp(const std::time_t& time){
			std::string timestamp(20, '0');
			char* buf = &timestamp[0];

			std::strftime(buf, 21, "%FT%TZ", std::gmtime(&time));
			setTimestamp(timestamp);

			return *this;
		}

		MessageEmbed setTimestamp(const std::string& timestamp = ""){
			if(!timestamp.empty()){
				embed["timestamp"] = timestamp;
			}else{
				setTimestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
			}

			return *this;
		};

		/**
		 * @returns JSON
		 */

		nlohmann::json getEmbed(){
			return embed;
		}

	protected:

		/**
		 * @name embed
		 * @protected
		 * @details MessageEmbed JSON storage.
		 */

		nlohmann::json embed;
	};
}
