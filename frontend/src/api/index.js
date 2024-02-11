import instance from "@/api/instance";
import authModule from "@/api/auth";

export default {
    auth: authModule(instance)
}