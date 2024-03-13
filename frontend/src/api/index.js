import instance from "@/api/instance";
import authModule from "@/api/auth";
import eventsModule from "@/api/events"
import usersModule from "@/api/users"
import sprintsModule from "@/api/sprints"
export default {
    auth: authModule(instance),
    events: eventsModule(instance),
    users: usersModule(instance),
    sprints: sprintsModule(instance),
}