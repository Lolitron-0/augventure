import instance from "@/api/instance";
import authModule from "@/api/auth";
import eventsModule from "@/api/events"
import usersModule from "@/api/users"

export default {
    auth: authModule(instance),
    events: eventsModule(instance),
<<<<<<< HEAD
=======
    users: usersModule(instance),
>>>>>>> 7a63c61e38ecf583e0460ad4a74a68c0cbfdc729
}