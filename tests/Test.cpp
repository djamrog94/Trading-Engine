#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orderbook/Orderbook.h"

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
		BOOST_TEST(bids[0].price_ > bids[1].price_);

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
		BOOST_TEST(bids[0].price_ >= bids[1].price_);

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
		BOOST_TEST(asks[0].price_ <= asks[1].price_);

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
		BOOST_TEST(asks[0].price_ <= asks[1].price_);

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
		BOOST_TEST(modifyOrderQuantity == bids[0].currentQuantity_);
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
}