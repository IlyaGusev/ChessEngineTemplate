#pragma once

#include <strategy.h>
#include <util.h>
#include <search/config.h>
#include <search/history_heuristics.h>
#include <search/transposition_table.h>

#include <unordered_map>
#include <string>

struct TSearchNode {
    lczero::Position Position;
    lczero::Move Move;
    size_t Depth = 0;
    size_t Ply = 0;
    mutable size_t TreeNodesCount = 1;

    TSearchNode(
        const lczero::Position& oldPosition,
        const lczero::Move& move,
        size_t depth,
        size_t ply
    )
        : Position(oldPosition, move), Move(move), Depth(depth), Ply(ply)
    {}

    TSearchNode(const lczero::Position& position, size_t depth, size_t ply)
        : Position(position), Move(), Depth(depth), Ply(ply)
    {}
};


class TSearchStrategy : public IStrategy {
public:
    explicit TSearchStrategy(
        const std::string& configFile
    ) : Config(configFile) {}

    explicit TSearchStrategy(
        const TSearchConfig& config
    ) : Config(config) {}

    std::optional<TMoveInfo> MakeMove(
        const lczero::PositionHistory& history
    ) override;

    const char* GetName() const override {
        return "Search";
    }

private:
    TMoveInfo Search(
        const TSearchNode& node,
        int alpha,
        int beta
    );

    TMoveInfo QuiescenceSearch(
        const TSearchNode& node,
        int alpha,
        int beta
    );

    int CalcMoveOrder(
        const lczero::Position& position,
        const lczero::Move& move,
        const lczero::Move& prevMove
    ) const;

private:
    TTranspositionTable TranspositionTable;
    THistoryHeuristics HistoryHeuristics;
    TSearchConfig Config;
};
