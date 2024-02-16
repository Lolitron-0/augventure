import instance from "@/api/instance";
import token_instance from "@/api/instance";
import authModule from "@/api/auth";
import eventsModule from "@/api/events"

export default {
    auth: authModule(instance),
    events: eventsModule(token_instance),
}