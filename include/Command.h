#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace Zork {
    
    class Game; // Forward declaration
    
    struct CommandResult {
        bool success;
        std::string message;
        bool continueGame;
        
        CommandResult(bool s = true, const std::string& m = "", bool c = true)
            : success(s), message(m), continueGame(c) {}
    };
    
    class Command {
    private:
        std::string verb_;
        std::vector<std::string> args_;
        
    public:
        Command(const std::string& input);
        
        std::string getVerb() const { return verb_; }
        std::vector<std::string> getArgs() const { return args_; }
        std::string getArgsAsString() const;
        bool hasArgs() const { return !args_.empty(); }
    };
    
    class CommandParser {
    private:
        Game* game_;
        std::map<std::string, std::vector<std::string>> commandAliases_;
        
        void setupAliases();
        std::string normalizeVerb(const std::string& verb);
        
    public:
        CommandParser(Game* game);
        
        CommandResult parse(const std::string& input);
        
        // Command handlers
        CommandResult handleMove(const Command& cmd);
        CommandResult handleLook(const Command& cmd);
        CommandResult handleExamine(const Command& cmd);
        CommandResult handleTake(const Command& cmd);
        CommandResult handleDrop(const Command& cmd);
        CommandResult handleInventory(const Command& cmd);
        CommandResult handleUse(const Command& cmd);
        CommandResult handleAttack(const Command& cmd);
        CommandResult handleScore(const Command& cmd);
        CommandResult handleSave(const Command& cmd);
        CommandResult handleLoad(const Command& cmd);
        CommandResult handleHelp(const Command& cmd);
        CommandResult handleQuit(const Command& cmd);
        
        std::string getHelpText() const;
    };
}

#endif // COMMAND_H
