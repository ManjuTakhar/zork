#include "../include/Command.h"
#include "../include/Game.h"
#include "../include/Utils.h"
#include <sstream>

namespace Zork {
    
    Command::Command(const std::string& input) {
        std::string trimmed = Utils::trim(input);
        std::vector<std::string> tokens = Utils::split(trimmed);
        
        if (!tokens.empty()) {
            verb_ = Utils::toLower(tokens[0]);
            args_ = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        }
    }
    
    std::string Command::getArgsAsString() const {
        return Utils::join(args_, " ");
    }
    
    CommandParser::CommandParser(Game* game) : game_(game) {
        setupAliases();
    }
    
    void CommandParser::setupAliases() {
        commandAliases_["n"] = {"north"};
        commandAliases_["s"] = {"south"};
        commandAliases_["e"] = {"east"};
        commandAliases_["w"] = {"west"};
        commandAliases_["u"] = {"up"};
        commandAliases_["d"] = {"down"};
        commandAliases_["l"] = {"look"};
        commandAliases_["x"] = {"examine"};
        commandAliases_["i"] = {"inventory"};
        commandAliases_["inv"] = {"inventory"};
        commandAliases_["get"] = {"take"};
        commandAliases_["pick"] = {"take"};
        commandAliases_["q"] = {"quit"};
        commandAliases_["exit"] = {"quit"};
        commandAliases_["?"] = {"help"};
        commandAliases_["kill"] = {"attack"};
        commandAliases_["fight"] = {"attack"};
    }
    
    std::string CommandParser::normalizeVerb(const std::string& verb) {
        if (commandAliases_.find(verb) != commandAliases_.end()) {
            return commandAliases_[verb][0];
        }
        return verb;
    }
    
    CommandResult CommandParser::parse(const std::string& input) {
        Command cmd(input);
        
        if (cmd.getVerb().empty()) {
            return CommandResult(true, "", true);
        }
        
        std::string verb = normalizeVerb(cmd.getVerb());
        
        // Movement commands
        if (verb == "north" || verb == "south" || verb == "east" || 
            verb == "west" || verb == "up" || verb == "down") {
            return handleMove(Command(verb));
        }
        else if (verb == "go" && cmd.hasArgs()) {
            return handleMove(Command(cmd.getArgs()[0]));
        }
        else if (verb == "look") {
            return handleLook(cmd);
        }
        else if (verb == "examine") {
            return handleExamine(cmd);
        }
        else if (verb == "take") {
            return handleTake(cmd);
        }
        else if (verb == "drop") {
            return handleDrop(cmd);
        }
        else if (verb == "inventory") {
            return handleInventory(cmd);
        }
        else if (verb == "use") {
            return handleUse(cmd);
        }
        else if (verb == "attack") {
            return handleAttack(cmd);
        }
        else if (verb == "score") {
            return handleScore(cmd);
        }
        else if (verb == "save") {
            return handleSave(cmd);
        }
        else if (verb == "load") {
            return handleLoad(cmd);
        }
        else if (verb == "help") {
            return handleHelp(cmd);
        }
        else if (verb == "quit") {
            return handleQuit(cmd);
        }
        
        return CommandResult(false, "I don't understand that command. Type 'help' for a list of commands.", true);
    }
    
    CommandResult CommandParser::handleMove(const Command& cmd) {
        std::string direction = normalizeVerb(cmd.getVerb());
        
        if (game_->getPlayer()->move(direction)) {
            game_->incrementMoves();
            game_->displayRoom();
            return CommandResult(true, "", true);
        }
        
        return CommandResult(false, "You can't go that way.", true);
    }
    
    CommandResult CommandParser::handleLook(const Command& cmd) {
        if (cmd.hasArgs()) {
            return handleExamine(cmd);
        }
        game_->displayRoom();
        return CommandResult(true, "", true);
    }
    
    CommandResult CommandParser::handleExamine(const Command& cmd) {
        if (!cmd.hasArgs()) {
            return CommandResult(false, "Examine what?", true);
        }
        
        std::string target = cmd.getArgsAsString();
        PlayerPtr player = game_->getPlayer();
        
        // Check inventory
        ItemPtr item = player->getInventoryItem(target);
        if (item) {
            return CommandResult(true, item->getDescription(), true);
        }
        
        // Check room
        item = player->getCurrentRoom()->getItem(target);
        if (item) {
            return CommandResult(true, item->getDescription(), true);
        }
        
        return CommandResult(false, "You don't see that here.", true);
    }
    
    CommandResult CommandParser::handleTake(const Command& cmd) {
        if (!cmd.hasArgs()) {
            return CommandResult(false, "Take what?", true);
        }
        
        std::string itemName = cmd.getArgsAsString();
        PlayerPtr player = game_->getPlayer();
        RoomPtr room = player->getCurrentRoom();
        
        ItemPtr item = room->removeItem(itemName);
        std::string message;
        
        if (player->takeItem(item, message)) {
            game_->addScore(5);
            return CommandResult(true, message, true);
        } else {
            if (item) {
                room->addItem(item); // Put it back if we couldn't take it
            }
            return CommandResult(false, message, true);
        }
    }
    
    CommandResult CommandParser::handleDrop(const Command& cmd) {
        if (!cmd.hasArgs()) {
            return CommandResult(false, "Drop what?", true);
        }
        
        std::string itemName = cmd.getArgsAsString();
        std::string message;
        
        bool success = game_->getPlayer()->dropItem(itemName, message);
        return CommandResult(success, message, true);
    }
    
    CommandResult CommandParser::handleInventory(const Command& cmd) {
        std::string inv = game_->getPlayer()->getInventoryList();
        return CommandResult(true, inv, true);
    }
    
    CommandResult CommandParser::handleUse(const Command& cmd) {
        if (!cmd.hasArgs()) {
            return CommandResult(false, "Use what?", true);
        }
        
        // TODO: Implement item usage system with context awareness
        // Items should interact with environment and other items
        return CommandResult(false, "You're not sure how to use that right now.", true);
    }
    
    CommandResult CommandParser::handleAttack(const Command& cmd) {
        // TODO: Implement full combat system with enemy encounters
        // Need to check for enemies in current room
        return CommandResult(false, "There's nothing here to attack.", true);
    }
    
    CommandResult CommandParser::handleScore(const Command& cmd) {
        game_->displayScore();
        return CommandResult(true, "", true);
    }
    
    CommandResult CommandParser::handleSave(const Command& cmd) {
        // TODO: Implement save functionality
        return CommandResult(false, "Save functionality is not yet implemented.", true);
    }
    
    CommandResult CommandParser::handleLoad(const Command& cmd) {
        // TODO: Implement load functionality
        return CommandResult(false, "Load functionality is not yet implemented.", true);
    }
    
    CommandResult CommandParser::handleHelp(const Command& cmd) {
        std::cout << getHelpText();
        return CommandResult(true, "", true);
    }
    
    CommandResult CommandParser::handleQuit(const Command& cmd) {
        return CommandResult(true, "Thanks for playing!", false);
    }
    
    std::string CommandParser::getHelpText() const {
        std::stringstream ss;
        ss << "\n=== Available Commands ===\n";
        ss << "Movement: north, south, east, west, up, down (or n, s, e, w, u, d)\n";
        ss << "Actions: look, examine <item>, take <item>, drop <item>\n";
        ss << "Inventory: inventory (or i, inv)\n";
        ss << "Combat: attack <enemy>, use <item>\n";
        ss << "Game: score, save, load, help, quit\n";
        ss << "========================\n";
        return ss.str();
    }
}
