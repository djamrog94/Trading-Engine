#include "TradingEngine/Exchange/TradingExchange.h"
namespace TradingEngine::Exchange {
    TradingExchange::TradingExchange() = default;
    //TradingExchange::TradingExchange(std::string yaml_file_path) : config_(YAML::LoadFile(yaml_file_path))
    //{
    //    //exchangeId_ = config_["TradingExxchangeConfiguration"]["ExchangeId"].as<int>();
    //    //exchangeName_ = config_["TradingExxchangeConfiguration"]["ExchangeName"].as<std::string>();
    //    //auto securities = config["TradingExxchangeConfiguration"]["Securities"].as<seq>();
    //    Instrument::Security sec = Instrument::Security(0, "FB", Orderbook::FillAllocationAlgorithm::Fifo);
    //    //orderbooks_.emplace(0, Orderbook::OrderbookFactory::createOrderbook(sec));
    //}


    int TradingEngine::Exchange::TradingExchange::getExchangeId()
    {
        return exchangeId_;
    }

    std::string TradingEngine::Exchange::TradingExchange::getExchangeName()
    {
        return exchangeName_;
    }

    bool TradingEngine::Exchange::TradingExchange::tryGetOrderbook(int securityId, Orderbook::RetrievalOrderbook& orderbook)
    {
        auto it = orderbooks_.find(securityId);
        if (it != orderbooks_.end()) return true;
        return false;
    }
}
