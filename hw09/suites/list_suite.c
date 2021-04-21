#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct user sample_user = { "Reemas", 2 };
static struct linked_list *_create_length_1_list(void) {
    struct linked_list *shortList = _create_list();
    _push_front(shortList, _create_user("Reemas", 2));
    return shortList;
}

static struct user sample_users[] = {
    { "Nrehtous", 1 },
    { "Reemas", 2 },
    { "Timud", 3 },
    { "Balec",  1 }
};

static struct linked_list *_create_longer_list(void) {
    struct linked_list *longerList = _create_list();
    // Push in reverse order
    _push_front(longerList, _create_user("Balec", 1));
    _push_front(longerList, _create_user("Timud", 3));
    _push_front(longerList, _create_user("Reemas", 2));
    _push_front(longerList, _create_user("Nrehtous", 1));
    return longerList;
}

/******************************************************************************/
/************************** create_list() tests *******************************/
/******************************************************************************/


START_TEST(test_list_create_list_basic) {
    struct linked_list *l = create_list();
    ck_assert_msg(l, "create_list should not return NULL");
    ck_assert_msg(!l->size, "create_list should return a list of size 0");
    ck_assert_msg(!l->head, "create_list should return a list with no head");
    free(l);
}
END_TEST


START_TEST(test_list_create_list_malloc_failure) {
    mallocs_until_fail = 0;
    struct linked_list *l = create_list();
    ck_assert_msg(!l, "create_list improperly handles malloc failure");
}
END_TEST


/******************************************************************************/
/************************** push_front() tests ********************************/
/******************************************************************************/

START_TEST(test_list_push_front_NULL_list) {
    ck_assert_msg(push_front(NULL, "Reemas", 2) != 0, "should not be able to push to a NULL list");
}
END_TEST

START_TEST(test_list_push_front_malloc_failure) {
    struct linked_list *l = _create_list();
    mallocs_until_fail = 0;
    
    int result = push_front(l, "Mr. Malloc", 2110);
    ck_assert_msg(result == 1, "push_front should return 1 on malloc failure");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_NULL_name) {
    struct linked_list *l = _create_list();
    
    struct user *user = _create_user(NULL, 100000);

    ck_assert_msg(push_front(l, NULL, 100000) == 0, "successful push_front should return 0");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should add a node");
    ck_assert_msg(!l->head->next, "you may be adding extra nodes somehow");
    ck_assert_msg(l->head->data, "push_front adds NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");
    
    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_empty) {
    struct linked_list *l = _create_list();

    char *name = "Teetu";
    struct user *user = _create_user(name, 4);

    ck_assert_msg(push_front(l, name, 4) == 0, "push_front should succeed on an empty list");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should should add a node to list");
    ck_assert_msg(!l->head->next, "push_front should only add one node");
    ck_assert_msg(l->head->data, "push_front adds NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_nonempty) {
    struct linked_list *l = _create_list();

    // push the stuffz
    _push_front(l, _create_user("Divad", 3));
    _push_front(l, _create_user("Elocin", 4));
    _push_front(l,  _create_user("Nrehtous", 85000));
    _push_front(l, _create_user("Hsimin", 3));

    char *name = "Naiviv";
    struct user *user = _create_user(name, 5);

    ck_assert_msg(push_front(l, name, 5) == 0, "push_front should return 0 on success");
    ck_assert_msg(l->size == 5, "push_front should increment size");
    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** push_back() tests *********************************/
/******************************************************************************/
START_TEST(test_list_push_back_empty) {
    struct linked_list *l = _create_list();
    
    char *name = "Ailuj";
    struct user *user = _create_user(name, 3);

    ck_assert_msg(push_back(l, name, 3) == 0, "push_back should succeed on an empty list");
    ck_assert(l->head);
    ck_assert_msg(l->head->data, "push_back should add a node with non-NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_back should add a node with correct data (double-check your create methods as well!)");
    ck_assert_msg(l->size == 1, "push_back should increment size");
    
    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_back_malloc_failure) {
    struct linked_list *l = _create_longer_list();
    mallocs_until_fail = 0;
    
    int result = push_back(l, "Callom", 69);
    ck_assert_msg(result == 1, "push_back should return 1 on malloc failure");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_back_non_empty) {
    struct linked_list *l = _create_list();
    ck_assert(l);

    struct user *user1 = _create_user("Ahos", 2);
    _push_front(l, user1);

    char *name = "Etnoc";
    struct user *user2 = _create_user(name, 150000);

    ck_assert_msg(push_back(l, name, 150000) == 0, "push_back should return 0 on success");
    ck_assert_msg(l->head->data, "push_back should not change front of list");
    ck_assert_msg(user_equal(l->head->data, user1), "push_back should not change front of list");
    ck_assert_msg(user_equal(l->head->next->data, user2), "push_back should add a node with correct data (double-check your create methods as well!)");
    ck_assert_msg(l->size == 2, "push_back should increment size");

    _free_user(user2);
    _free_list(l); // will free user1
}
END_TEST

START_TEST(test_list_push_back_NULL) {
    struct linked_list *l = _create_list();

    char *name = "Akinrav";
    struct user *user = _create_user(NULL, 3);

    ck_assert_msg(push_back(NULL, name, 3) != 0, "push_back shouldn't return 0 with NULL list");
    ck_assert_msg(push_back(l, NULL, 3) == 0, "push_back should return 0 with NULL data and non-NULL list");
    ck_assert_msg(l->size == 1, "push_back should increase size");
    ck_assert_msg(l->head->data, "adding NULL name should add non-NULL struct user with NULL name (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "adding NULL name should add struct user with NULL name (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** remove_at_index() tests *************************/
/******************************************************************************/
START_TEST(test_list_remove_at_index_NULL_list) {
    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(remove_at_index(NULL, &dataOut, 0) != 0, "remove_at_index shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_remove_at_index_NULL_dataOut) {
    struct linked_list *l = _create_length_1_list();
    ck_assert_msg(remove_at_index(l, NULL, 0) != 0, "remove_at_index shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_out_of_bounds) {
    struct linked_list *l = _create_length_1_list();
    ck_assert_msg(remove_at_index(l, NULL, -1) != 0, "remove_at_index shouldn't return 0 when out of bounds");
    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_front) {
    struct linked_list *l = _create_longer_list();
    struct user *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[0]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[1]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[2]));

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_middle) {
    struct linked_list *l = _create_longer_list();
    struct user *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 1);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[1]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[2]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_back) {
    struct linked_list *l = _create_longer_list();
    struct user *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 3);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[3]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[2]));

    ck_assert(!l->head->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_length_1) {
    struct linked_list *l = _create_length_1_list();
    struct user *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_user);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** add_at_index() tests ***************************************/
/******************************************************************************/
START_TEST(test_list_add_at_index_out_of_bounds) {
    struct linked_list *l = _create_list();

    char *name = "Wehttam";

    ck_assert_msg(add_at_index(l, -1, name, 2) != 0, "add_at_index shouldn't return 0 for index < 0");
    _push_front(l, _create_user(name, 2));
    ck_assert_msg(add_at_index(l, 2, name, 2) != 0, "add_at_index shouldn't return 0 for index >= size");

    // free_list will free the rest of the data since we manually inserted it at the head
    _free_list(l);

}
END_TEST

START_TEST(test_list_add_at_index_empty_list) {
    struct linked_list *l = _create_list();

    char *name1 = "Kcirtap";
    struct user *user1 = _create_user(name1, 3);

    char *name2 = "Tsugua";

    ck_assert(add_at_index(l, 0, name1, 3) == 0);
    ck_assert_int_eq(l->size, 1);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, user1));

    ck_assert_msg(add_at_index(l, 2, name2, 125000) != 0, "add_at_index shouldn't return 0 for index >= size");
    ck_assert_msg(add_at_index(l, 1, name2, 125000) == 0, "add_at_index should return 0 when successful");

    ck_assert_int_eq(l->size, 2);

    _free_user(user1);
    _free_list(l);
}
END_TEST

START_TEST(test_list_add_at_index_non_empty_list) {
    struct linked_list *l = _create_longer_list();

    char *name = "Ellebasi";
    struct user *user = _create_user(name, 4);

    ck_assert_msg(add_at_index(l, 1, name, 4) == 0, "add_at_index should return 0 when successful");

    ck_assert(l->head);
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, user));

    ck_assert_int_eq(l->size, 5);

    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_add_at_index_NULL) {
    struct linked_list *l = _create_list();
    
    struct user *user = _create_user(NULL, 3);

    ck_assert_msg(add_at_index(NULL, 0, NULL, 3) != 0, "add_at_index shouldn't return 0 for NULL list");
    ck_assert_msg(add_at_index(NULL, 0, "Yeroc", 3) != 0, "add_at_index shouldn't return 0 for NULL list");

    ck_assert_msg(add_at_index(l, 0, NULL, 3) == 0, "add_at_index shouldn't fail with NULL name");
    ck_assert_int_eq(l->size, 1);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, user));

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/*************************** pop_front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_front_NULL_list) {
    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(pop_front(NULL, &dataOut) != 0, "pop_front shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_pop_front_NULL_dataOut) {
    struct linked_list *l = _create_list();
    ck_assert_msg(pop_front(l, NULL) != 0, "pop_front shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_empty) {
    struct linked_list *l = _create_list();
    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(pop_front(l, &dataOut) != 0, "pop_front shouldn't return 0 when called with empty list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_nonempty) {
    struct linked_list *l = _create_length_1_list();
    struct user *user = NULL;
    int result = pop_front(l, &user);
    ck_assert_msg(user, "pop_front should set dataOut on success");
    int userCheck = user_equal(user, &sample_user);
    _free_user(user);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 0);

    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_longer_list) {
    struct linked_list *l = _create_longer_list();
    struct user *data = NULL;
    int result = pop_front(l, &data);
    ck_assert_msg(data, "pop_front should set dataOut on success");
    int userCheck = user_equal(data, &sample_users[0]);
    _free_user(data);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert_msg(user_equal(l->head->data, &sample_users[1]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert_msg(user_equal(l->head->next->data, &sample_users[2]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert_msg(user_equal(l->head->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next);

    result = pop_front(l, &data);
    ck_assert(data);
    userCheck = user_equal(data, &sample_users[1]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 2);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[2]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** pop_back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_back_NULL_list) {
    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(pop_back(NULL, &dataOut) != 0, "pop_back shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_pop_back_NULL_dataOut) {
    struct linked_list *l = _create_list();
    ck_assert_msg(pop_back(l, NULL) != 0, "pop_back shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_empty) {
    struct linked_list *l = _create_list();
    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(pop_back(l, &dataOut) != 0, "pop_back shouldn't return 0 when called with empty list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_nonempty) {
    struct linked_list *l = _create_length_1_list();
    struct user *user = NULL;
    int result = pop_back(l, &user);
    ck_assert_msg(user, "pop_back should set dataOut on success");

    int userCheck = user_equal(user, &sample_user);
    _free_user(user);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 0);

    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_longer_list) {
    struct linked_list *l = _create_longer_list();
    struct user *data = NULL;
    int result = pop_back(l, &data);
    ck_assert(data);

    int userCheck = user_equal(data, &sample_users[3]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));
    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[2]));

    ck_assert(!l->head->next->next->next);

    result = pop_back(l, &data);
    userCheck = user_equal(data, &sample_users[2]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 2);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));

    ck_assert(!l->head->next->next);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/******************************* get() tests **********************************/
/******************************************************************************/
// helper method for get() tests
void checkLongerListUnchanged(struct linked_list *l, char *msg) {
    ck_assert_msg(user_equal(l->head->data, &sample_users[0]), msg);
    ck_assert_msg(user_equal(l->head->next->data, &sample_users[1]), msg);
    ck_assert_msg(user_equal(l->head->next->next->data, &sample_users[2]), msg);
    ck_assert_msg(user_equal(l->head->next->next->next->data, &sample_users[3]), msg);
    ck_assert_msg(!l->head->next->next->next->next, msg);
}

START_TEST(test_list_get_NULL_list) {
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(NULL, 0, &u) != 0, "get shouldn't return 0 when called with NULL list");
}
END_TEST

START_TEST(test_list_get_NULL_dataOut) {
    struct linked_list *l = _create_longer_list();
    ck_assert_msg(get(l, 0, NULL) != 0, "get shouldn't return 0 when called with NULL dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_negative_index) {
    struct linked_list *l = _create_longer_list();
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(l, -1, &u) != 0, "get shouldn't return 0 when called with index < 0");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_front) {
    struct linked_list *l = _create_longer_list();
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 0, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[0]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_middle) {
    struct linked_list *l = _create_longer_list();
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 1, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[1]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_back) {
    struct linked_list *l = _create_longer_list();
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 2, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[2]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_out_of_bounds_index) {
    struct linked_list *l = _create_longer_list();
    struct user *u = (struct user*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 4, &u) != 0, "get shouldn't return 0 when called with index >= size");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** contains() tests ********************************/
/******************************************************************************/

START_TEST(test_list_contains_NULL_list) {
    struct user *user = _create_user("Draheraseman", 3);

    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    int result = contains(NULL, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when called with NULL list");
}
END_TEST

START_TEST(test_list_contains_NULL_dataOut) {
    struct linked_list *l = _create_longer_list();

    // this is a terrible joke
    struct user *user = _create_user("Dr. LC-3, Human-Cyborg Relations", 10000000);

    int result = contains(l, user, NULL);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when called with NULL dataOut");
    checkLongerListUnchanged(l, "list was changed by contains method");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_empty) {
    struct linked_list *l = _create_list();

    struct user *user = _create_user("Dr. Seuss", 200000);

    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when data not found");
    ck_assert_msg(!dataOut, "contains should set dataOut=NULL when data not found");

    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_not_contained) {
    struct linked_list *l = _create_longer_list();

    struct user *user = _create_user("Mr. Unknown", 8);

    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when data not found");
    ck_assert_msg(!dataOut, "contains should set dataOut=NULL when data not found");
    checkLongerListUnchanged(l, "list was changed by contains method");

    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_NULL_name) {
    struct linked_list *l = _create_longer_list();

    struct user *user = _create_user(NULL, 4);

    _push_front(l, _create_user(NULL, 4));

    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    ck_assert_msg(result, "contains should return 1 (TRUE) when data is found");
    ck_assert_msg(dataOut != user, "contains should set dataOut to the value in the list, not the one passed in");
    ck_assert_msg(user_equal(dataOut, user), "contains should set dataOut to the value in the list that matches the value passed in");

    dataOut = _pop_front(l);
    _free_user(dataOut);
    _free_user(user);

    checkLongerListUnchanged(l, "list was changed by contains method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_is_contained) {
    struct linked_list *l = _create_longer_list();

    struct user *dataOut = (struct user*) 0xDEADBEEFU;
    int result = contains(l, &sample_users[1], &dataOut);

    ck_assert_msg(result, "contains should return 1 (TRUE) when data is found");
    ck_assert_msg(dataOut != &sample_users[1], "contains should set dataOut to the value in the list, not the one passed in");
    ck_assert_msg(user_equal(dataOut, &sample_users[1]), "contains should set dataOut to the value in the list that matches the value passed in");

    checkLongerListUnchanged(l, "list was changed by contains method");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/

/* NOTE: passing these tests does not mean that there are no memory leaks!
This is an easy method to accidentally cause memory leaks on, so be sure to run Valgrind! */

START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    empty_list(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    struct linked_list *l = _create_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    struct linked_list *l = _create_length_1_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    struct linked_list *l = _create_longer_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** replace_name_at_index() tests *********************/
/******************************************************************************/

START_TEST(test_list_replace_name_at_index_NULL_list) {
    struct linked_list *l = NULL;

    int result = replace_name_at_index(l, 0, "Harold");
    ck_assert_msg(result != 0, "replace_name_at_index shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_replace_name_at_index_low_invalid_index) {
    struct linked_list *l = _create_longer_list();

    int result = replace_name_at_index(l, -1, "Kaylee");
    ck_assert_msg(result != 0, "replace_name_at_index shouldn't return 0 with an invalid index");
    checkLongerListUnchanged(l, "list was changed by an invalid replace_name_at_index call");

    _free_list(l);
}
END_TEST

START_TEST(test_list_replace_name_at_index_high_invalid_index) {
    struct linked_list *l = _create_longer_list();

    int result = replace_name_at_index(l, 4, "Parthiv");
    ck_assert_msg(result != 0, "replace_name_at_index shouldn't return 0 with an invalid index");
    checkLongerListUnchanged(l, "list was changed by an invalid replace_name_at_index call");

    _free_list(l);
}
END_TEST

START_TEST(test_list_replace_name_at_index_list_length_1) {
    struct linked_list *l = _create_length_1_list();

    int result = replace_name_at_index(l, 0, "Olivia");
    ck_assert_msg(result == 0, "replace_name_at_index should return 0 (FALSE) when it receives valid parameters");
    ck_assert_msg(l->size == 1, "replace_name_at_index should not change list size");
    ck_assert(l->head);
    ck_assert(l->head->data->id == sample_user.id);
    ck_assert(strcmp(l->head->data->name, "Olivia") == 0);
    ck_assert(!l->head->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_replace_name_at_index_shorter_name) {
    struct linked_list *l = _create_longer_list();

    int result = replace_name_at_index(l, 2, "Ed");
    ck_assert_msg(result == 0, "replace_name_at_index should return 0 (FALSE) when it receives valid parameters");
    ck_assert_msg(l->size == 4, "replace_name_at_index should not change list size");
    
    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));
    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    
    ck_assert(l->head->next->next->data->id == sample_users[2].id);
    ck_assert(strcmp(l->head->next->next->data->name, "Ed") == 0);

    ck_assert(l->head->next->next->next);
    ck_assert(l->head->next->next->next->data);
    ck_assert(user_equal(l->head->next->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_replace_name_at_index_longer_name) {
    struct linked_list *l = _create_longer_list();

    int result = replace_name_at_index(l, 2, "Miss Supercalifragilisticexpialidocious");
    ck_assert_msg(result == 0, "replace_name_at_index should return 0 (FALSE) when it receives valid parameters");
    ck_assert_msg(l->size == 4, "replace_name_at_index should not change list size");
    
    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));
    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    
    ck_assert(l->head->next->next->data->id == sample_users[2].id);
    ck_assert(strcmp(l->head->next->next->data->name,
        "Miss Supercalifragilisticexpialidocious") == 0);

    ck_assert(l->head->next->next->next);
    ck_assert(l->head->next->next->next->data);
    ck_assert(user_equal(l->head->next->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_replace_name_at_index_realloc_failure) {
    struct linked_list *l = _create_longer_list();
    mallocs_until_fail = 0;

    int result = replace_name_at_index(l, 1, "Barnabus");
    ck_assert_msg(result == 1, "replace_name_at_index should return 1 on realloc failure");
    
    _free_list(l);
}
END_TEST


/**
 * TODO: add tests for replace name at index
 * @Charlie
 */

Suite *list_suite(void) {
    Suite *s = suite_create("struct linked_list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_malloc_failure);

    // push_front() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_NULL_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_nonempty);


    // push_back() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_non_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_NULL);

    // remove_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_front);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_middle);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_back);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_length_1);

    // pop_front() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_longer_list);

    // pop_back() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_longer_list);

    // add_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_empty_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_non_empty_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_NULL);

    // get() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_front);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_middle);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_back);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_out_of_bounds_index);

    // contains() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_not_contained);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_is_contained);

    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_longer_list);

    // replace_name_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_low_invalid_index);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_high_invalid_index);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_shorter_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_longer_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_replace_name_at_index_realloc_failure);
  
    return s;
}
