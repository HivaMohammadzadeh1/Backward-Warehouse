# Backward-Warehouse

Write a menu-driven program to handle the flow of widgets into and out of a warehouse.

The warehouse will have numerous deliveries of new widgets and orders for widgets
The widgets in a filled order are billed at a profit of 50 percent over their cost
Each delivery of new widgets may have a different cost associated with it
The accountants for the firm have instituted a last-in, first-out system for filling orders
the newest widgets are the first ones sent out to fill an order and the most recent orders are filled first
partial shipments allowed
10 widgets were ordered and warehouse has only 4 available, ship 4, the remainder 6 will be shipped later
Assign unique numbers to each order and each delivery
This function of inventory can be represented using two stacks: orders-to-be-filled and widgets-on-hand. When delivery of new widgets is received, any unfilled orders (on the orders-to-be-filled stack) are processed and filled. After all orders are filled, if there are widgets remaining in the new delivery, a new element is pushed onto the widgets-on- hand stack. When an order for new widgets is received, one or more objects are popped from the widgets-on-hand stack until the order has been filled.
If the order is completely filled and there are widgets left over in the last object popped, a modified object with the quantity updated is pushed onto the widgets-on-hand stack.
If the order is not completely filled, the order is pushed onto the orders-to-be-filled stack with an updated quantity of widgets to be sent out later.
After an order is fully or a partially filled display the following in the format shown below:
order number
quantity ordered
quantity shipped
price  per widget  and the total cost for all widgets in the order
indicate whether there are any widgets remaining to be sent out at a later time.
After delivery is processed, display information about each order that was filled with this delivery.
Keep track of the number of widgets in stock and the number of widgets shipped.
Make sure each function definition is preceded by  a description, post/preconditions
Create menu options to display the  details of the inventory on hand ( delivery stack) and the details of the outstanding orders (shipment/order stack)
You may implement the stack as an array or a linked list
Well format the output: all numbers should be right-aligned; see the sample below
Create a test plan ( hand-written or typed); the test plan has to be approved for the instructor before you can submit the lab.
Order Number	123			
Qty to Ordered	25			
Qty Shipped this Shipment	10			
Qty to be Shipped	5			
Total Cost to the Warehouse	28.25			
Total Cost to the Customer	42.38			
Profit this  Shipment	14.13			
Shipment details				
Delivery #	Qty Shipped	Unit Price	Cost to the Warehouse	Cost to the Customer
621	5	2.5	12.5	18.75
620	3	1.75	5.25	7.88
619	2	5.25	10.5	15.75
