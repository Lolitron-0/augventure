import api from "@/api/index"

export default {
    install(app) {
        app.config.globalProperties.$api = api
    }
}
