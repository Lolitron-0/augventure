import { createApp } from 'vue'
import App from './App'
import router from "@/router/router";
import components from "core-js/stable/dom-collections";
import Vuelidate from 'vuelidate'
import ApiPlugin from "@/plugins/api"
import store from "@/store/index.js"

const app = createApp(App)

components.forEach(component => {
    app.component(component.name, component)
})

app
    // .use(Vuelidate)
    .use(store)
    .use(ApiPlugin)
    .use(router)
    .mount('#app')
