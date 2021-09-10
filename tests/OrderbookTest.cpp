#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/Trade.h"
#include "TradingEngine/Orderbook/OrderIdGenerator.h"
#include "TradingEngine/Orderbook/FifoOrderbook.h"

namespace TradingEngine {
	Orders::OrderCore oc = Orders::OrderCore(0, "test", 0);
	BOOST_AUTO_TEST_CASE(orderCoreMemberTest)
	{
		BOOST_TEST(oc.getOrderId() == 0);
		BOOST_TEST(oc.getSecurityId() == 0);
		BOOST_TEST(oc.getUsername() == "test");
	}
	BOOST_AUTO_TEST_CASE(orderbookAddOrderOneBidOrderTest)
	{
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		Orders::Order o = Orders::Order(oc, 5, 10, true);
		ob.addOrder(o);
		BOOST_TEST(ob.getCount() == 1);
	}
	BOOST_AUTO_TEST_CASE(orderbookAddOrderOneBidOrderOneAskOrderTest)
	{
		Orders::OrderCore oc1 = Orders::OrderCore(1, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(2, "test2", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc2, 5, 1000, true));
		ob.addOrder(Orders::Order(oc1, 5, 1000, false));
		BOOST_TEST(ob.getCount() == 2);
	}
	BOOST_AUTO_TEST_CASE(orderbookAddOrderTwoBidOrderOneAskOrderTest)
	{
		Orders::OrderCore oc1 = Orders::OrderCore(1, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(2, "test2", 1);
		Orders::OrderCore oc3 = Orders::OrderCore(3, "test3", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc2, 5, 1000, true));
		ob.addOrder(Orders::Order(oc3, 5, 1001, true));
		ob.addOrder(Orders::Order(oc1, 5, 1000, false));
		BOOST_TEST(ob.getBidOrders().size() == 2);
		BOOST_TEST(ob.getCount() == 3);
	}
	BOOST_AUTO_TEST_CASE(orderbookAddOrderRemoveOrder)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		ob.removeOrder(Orders::CancelOrder(oc2));
		BOOST_TEST(ob.getCount() == 0);

	}
	BOOST_AUTO_TEST_CASE(orderbookAddOrderRemoveOrderCheckBids)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		ob.removeOrder(Orders::CancelOrder(oc2));
		std::vector bids = ob.getBidOrders();
		BOOST_TEST(bids.size() == 0);

	}
	BOOST_AUTO_TEST_CASE(orderbookAddTheeBidOrderRemoveOrderMiddle)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orders::OrderCore oc3 = Orders::OrderCore(2, "test1", 1);
		Orders::OrderCore oc4 = Orders::OrderCore(3, "test1", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc3, 1, 1001, true));
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		ob.removeOrder(Orders::CancelOrder(oc2));
		ob.addOrder(Orders::Order(oc4, 10, 1001, true));
		std::vector bids = ob.getBidOrders();
		BOOST_TEST(bids.size() == 2);

	}
	BOOST_AUTO_TEST_CASE(orderbookAddBidOrderSamePriceRemoveMiddle)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orders::OrderCore oc3 = Orders::OrderCore(2, "test1", 1);
		Orders::OrderCore oc4 = Orders::OrderCore(3, "test1", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc3, 5, 1001, true));
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		ob.removeOrder(Orders::CancelOrder(oc2));
		ob.addOrder(Orders::Order(oc4, 5, 1001, true));
		std::vector bids = ob.getBidOrders();
		BOOST_TEST(bids.size() == 2);
		BOOST_TEST((*bids[0]).getCurrent().price_ >= (*bids[1]).getCurrent().price_);

	}
	BOOST_AUTO_TEST_CASE(orderbookAddTheeAskOrderRemoveOrderMiddle)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orders::OrderCore oc3 = Orders::OrderCore(2, "test1", 1);
		Orders::OrderCore oc4 = Orders::OrderCore(3, "test1", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc3, 1, 1001, false));
		ob.addOrder(Orders::Order(oc1, 5, 1001, false));
		ob.removeOrder(Orders::CancelOrder(oc2));
		ob.addOrder(Orders::Order(oc4, 10, 1001, false));
		std::vector asks = ob.getAskOrders();
		BOOST_TEST(asks.size() == 2);
		BOOST_TEST((*asks[0]).getCurrent().price_ <= (*asks[1]).getCurrent().price_);

	}
	BOOST_AUTO_TEST_CASE(orderbookAddAskOrderSamePriceRemoveMiddle)
	{
		const long orderId = 0;
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(orderId, "test2", 1);
		Orders::OrderCore oc3 = Orders::OrderCore(2, "test1", 1);
		Orders::OrderCore oc4 = Orders::OrderCore(3, "test1", 1);
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		ob.addOrder(Orders::Order(oc3, 5, 1001, false));
		ob.addOrder(Orders::Order(oc1, 5, 1001, false));
		ob.removeOrder(Orders::CancelOrder(oc2));
		ob.addOrder(Orders::Order(oc4, 5, 1001, false));
		std::vector asks = ob.getAskOrders();
		BOOST_TEST(asks.size() == 2);
		BOOST_TEST((*asks[0]).getCurrent().price_ <= (*asks[1]).getCurrent().price_);

	}

	// modify order
	BOOST_AUTO_TEST_CASE(orderbookModifyOrder)
	{
		const long orderId = 0;
		const uint16_t modifyOrderQuantity = 5;
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		Orderbook::OrderBookResult res = ob.changeOrder(Orders::ModifyOrder(oc1, 1000, modifyOrderQuantity, true));
		std::vector bids = ob.getBidOrders();
		BOOST_TEST(bids.size() == 1);
		BOOST_TEST(modifyOrderQuantity == (*bids[0]).getCurrent().currentQuantity_);
		BOOST_TEST(res.hasModifyOrderStatuses() == true);

	}
	// modify order wrong side

	BOOST_AUTO_TEST_CASE(orderbookModifyOrderWrongSide)
	{
		const long orderId = 0;
		const uint16_t modifyOrderQuantity = 5;
		Orderbook::Orderbook ob = Orderbook::Orderbook();
		Orders::OrderCore oc1 = Orders::OrderCore(orderId, "test1", 1);
		ob.addOrder(Orders::Order(oc1, 5, 1001, true));
		Orderbook::OrderBookResult res = ob.changeOrder(Orders::ModifyOrder(oc1, 1000, modifyOrderQuantity, false));
		std::vector bids = ob.getBidOrders();
		BOOST_TEST(bids.size() == 1);
		BOOST_TEST(res.hasRejections() == true);

	}
	// spread

	// trade
	BOOST_AUTO_TEST_CASE(testCaseTradeNumber)
	{
		Orders::OrderCore oc1 = Orders::OrderCore(1, "test1", 1);
		Orders::Order od1 = Orders::Order(oc1, 5, 1001, false);
		uint16_t quant = 16;
		Orders::OrderCore oc2 = Orders::OrderCore(2, "test1", 1);
		Orders::Order od2 = Orders::Order(oc2, 2, 1001, false);
		Orderbook::Trade trade1 = Orderbook::Trade(od1, quant);
		Orderbook::Trade trade2 = Orderbook::Trade(od2, quant);
		BOOST_TEST(trade1.getTradeNumber() == 1);
		BOOST_TEST(trade2.getTradeNumber() == 2);
	}

	BOOST_AUTO_TEST_CASE(testOrderIdGenerator)
	{
		long first = Orderbook::OrderIdGenerator::generateOrderId();
		long second = Orderbook::OrderIdGenerator::generateOrderId();
		BOOST_TEST(second == first + 1);

	}
	BOOST_AUTO_TEST_CASE(FifoOrderbookTwoOrdersPerfectMatch)
	{
		Orders::OrderCore oc1 = Orders::OrderCore(1, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(2, "test1", 1);
		Orderbook::Orderbook* ob = new Orderbook::Orderbook();
		Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm* test = new Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm();
		Orderbook::FifoOrderbook fifoMatcher = Orderbook::FifoOrderbook(ob, test);
		// price, quantity
		Orders::Order askOrder = Orders::Order(oc1, 10000, 5, false);
		Orders::Order buyOrder = Orders::Order(oc2, 10001, 5, true);
		fifoMatcher.addOrder(askOrder);
		fifoMatcher.addOrder(buyOrder);
		auto results = fifoMatcher.match();

		BOOST_TEST(results.MatchResult.getFills().size() == 2);
		BOOST_TEST(results.MatchResult.getTrades().size() == 1);
		BOOST_TEST(results.OrderBookResult.hasCancelOrderStatuses() == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(1) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(2) == false);

	}
	BOOST_AUTO_TEST_CASE(FifoOrderbookTwoOrdersBidRemainsResting)
	{
		Orders::OrderCore oc1 = Orders::OrderCore(1, "test1", 1);
		Orders::OrderCore oc2 = Orders::OrderCore(2, "test1", 1);
		Orderbook::Orderbook* ob = new Orderbook::Orderbook();
		Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm* test = new Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm();
		Orderbook::FifoOrderbook fifoMatcher = Orderbook::FifoOrderbook(ob, test);
		// price, quantity
		Orders::Order askOrder = Orders::Order(oc1, 10000, 10, false);
		Orders::Order buyOrder = Orders::Order(oc2, 10001, 15, true);
		fifoMatcher.addOrder(askOrder);
		fifoMatcher.addOrder(buyOrder);
		auto results = fifoMatcher.match();

		BOOST_TEST(results.MatchResult.getFills().size() == 2);
		BOOST_TEST(results.MatchResult.getTrades().size() == 1);
		BOOST_TEST(results.OrderBookResult.hasCancelOrderStatuses() == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(1) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(2) == true);

	}
	BOOST_AUTO_TEST_CASE(FifoOrderbookThreeOrdersBidRemainsResting)
	{
		const long askOrderOrderId = 0;
		const long buyOrderOrderId = 1;
		const long buySecondOrderOrderId = 2;
		Orders::OrderCore ao = Orders::OrderCore(askOrderOrderId, "test1", 1);
		Orders::OrderCore bo = Orders::OrderCore(buyOrderOrderId, "test1", 1);
		Orders::OrderCore bo2 = Orders::OrderCore(buySecondOrderOrderId, "test1", 1);
		Orderbook::Orderbook* ob = new Orderbook::Orderbook();
		Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm* test = new Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm();
		Orderbook::FifoOrderbook fifoMatcher = Orderbook::FifoOrderbook(ob, test);
		// price, quantity
		Orders::Order askOrder = Orders::Order(ao, 10000, 20, false);
		Orders::Order buyOrder = Orders::Order(bo, 10001, 15, true);
		Orders::Order buyOrder2 = Orders::Order(bo2, 10001, 15, true);
		fifoMatcher.addOrder(askOrder);
		fifoMatcher.addOrder(buyOrder);
		fifoMatcher.addOrder(buyOrder2);
		auto results = fifoMatcher.match();

		BOOST_TEST(results.MatchResult.getFills().size() == 4);
		BOOST_TEST(results.MatchResult.getTrades().size() == 2);
		BOOST_TEST(results.OrderBookResult.hasCancelOrderStatuses() == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(askOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buyOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buySecondOrderOrderId) == true);

	}
	BOOST_AUTO_TEST_CASE(FifoOrderbookThreeOrdersAskRemainsResting)
	{
		const long askOrderOrderId = 0;
		const long buyOrderOrderId = 1;
		const long buySecondOrderOrderId = 2;
		const long askPrice = 10000;
		Orders::OrderCore ao = Orders::OrderCore(askOrderOrderId, "test1", 1);
		Orders::OrderCore bo = Orders::OrderCore(buyOrderOrderId, "test1", 1);
		Orders::OrderCore bo2 = Orders::OrderCore(buySecondOrderOrderId, "test1", 1);
		Orderbook::Orderbook* ob = new Orderbook::Orderbook();
		Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm* test = new Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm();
		Orderbook::FifoOrderbook fifoMatcher = Orderbook::FifoOrderbook(ob, test);
		// price, quantity
		Orders::Order askOrder = Orders::Order(ao, askPrice, 100, false);
		Orders::Order buyOrder = Orders::Order(bo, 10001, 15, true);
		Orders::Order buyOrder2 = Orders::Order(bo2, 10001, 15, true);
		fifoMatcher.addOrder(askOrder);
		fifoMatcher.addOrder(buyOrder);
		fifoMatcher.addOrder(buyOrder2);
		auto results = fifoMatcher.match();
		auto spread = fifoMatcher.getSpread();

		BOOST_TEST(results.MatchResult.getFills().size() == 4);
		BOOST_TEST(results.MatchResult.getTrades().size() == 2);
		BOOST_TEST(results.OrderBookResult.hasCancelOrderStatuses() == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(askOrderOrderId) == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buyOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buySecondOrderOrderId) == false);
		BOOST_TEST(askPrice == spread.getAsk().value());
		BOOST_TEST(NULL == spread.getBid().value());


	}
	BOOST_AUTO_TEST_CASE(FifoOrderbookFourOrdersPerfectMatch)
	{
		const long askOrderOrderId = 0;
		const long asksecondOrderOrderId = 1;
		const long buyOrderOrderId = 2;
		const long buySecondOrderOrderId = 3;
		const long askPrice = 10000;
		const long bidPrice = 10001;
		Orders::OrderCore ao = Orders::OrderCore(askOrderOrderId, "test1", 1);
		Orders::OrderCore ao2 = Orders::OrderCore(asksecondOrderOrderId, "test1", 1);
		Orders::OrderCore bo = Orders::OrderCore(buyOrderOrderId, "test1", 1);
		Orders::OrderCore bo2 = Orders::OrderCore(buySecondOrderOrderId, "test1", 1);
		Orderbook::Orderbook* ob = new Orderbook::Orderbook();
		Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm* test = new Orderbook::MatchingAlgorithm::FifoMatchingAlgorithm();
		Orderbook::FifoOrderbook fifoMatcher = Orderbook::FifoOrderbook(ob, test);
		// price, quantity
		Orders::Order askOrder = Orders::Order(ao, askPrice, 10, false);
		Orders::Order askOrder2 = Orders::Order(ao2, askPrice, 20, false);
		Orders::Order buyOrder = Orders::Order(bo, bidPrice, 15, true);
		Orders::Order buyOrder2 = Orders::Order(bo2, bidPrice, 15, true);
		fifoMatcher.addOrder(askOrder);
		fifoMatcher.addOrder(askOrder2);
		fifoMatcher.addOrder(buyOrder);
		fifoMatcher.addOrder(buyOrder2);
		auto results = fifoMatcher.match();
		auto spread = fifoMatcher.getSpread();

		BOOST_TEST(results.MatchResult.getFills().size() == 6);
		BOOST_TEST(results.MatchResult.getTrades().size() == 3);
		BOOST_TEST(results.OrderBookResult.hasCancelOrderStatuses() == true);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(askOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(asksecondOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buyOrderOrderId) == false);
		BOOST_TEST(fifoMatcher.orderbook_->containsOrder(buySecondOrderOrderId) == false);
		BOOST_TEST(NULL == spread.getAsk().value());
		BOOST_TEST(NULL == spread.getBid().value());


	}


}