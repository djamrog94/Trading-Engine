#include "../include/TradingEngine/Orders/OrderCore.h"
#include "../include/TradingEngine/Orderbook/Orderbook.h"
#include "../include/TradingEngine/Orderbook/Trade.h"
#include "../include/TradingEngine/Orderbook/OrderIdGenerator.h"
#include "../include/TradingEngine/Orderbook/FifoOrderbook.h"
#include "../include/TradingEngine/Orderbook/OrderbookFactory.h"
#include <chrono>
#include <cctype>
#include <random>
int main()
{
	// price, quantity


	using u32 = uint_least32_t;
	using engine = std::mt19937;

	int total = 0;
	int trades = 0;
	for (int it = 0; it < 10; it++)
	{
		const int askOrderOrderId = 1;
		TradingEngine::Orders::OrderCore ao = TradingEngine::Orders::OrderCore(askOrderOrderId, "test1", 1);
		TradingEngine::Orderbook::MatchingOrderbook fifoMatcher = TradingEngine::Orderbook::OrderbookFactory::createOrderbook(TradingEngine::Instrument::Security());

		std::random_device os_seed;
		const u32 seed = os_seed();

		engine generator(seed);
		std::uniform_int_distribution< u32 > distribute(1, 10);
		std::vector<TradingEngine::Orders::Order> orders;
		bool buy;
		for (int i = 0; i < 100000; i++)
		{
			if (i % 2 == 0)
				buy = true;
			else
				buy = false;
			orders.push_back(TradingEngine::Orders::Order(ao, distribute(generator), distribute(generator), buy));
		}
		for (auto order : orders)
			fifoMatcher.addOrder(order);

		std::chrono::time_point<std::chrono::high_resolution_clock> startPoint = std::chrono::high_resolution_clock::now();
		auto results = fifoMatcher.match();
		std::chrono::time_point<std::chrono::high_resolution_clock> endPoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();
		trades += results.getTrades().size();
		orders.clear();
		auto duration = end - start;
		std::cout << "Iteration " << it << ": " << duration << std::endl;
		std::cout << "Iteration " << it << ": " << results.getTrades().size() << "trades" << std::endl;
		total += duration;
	}
	std::cout << total << std::endl;
	return 0;
}