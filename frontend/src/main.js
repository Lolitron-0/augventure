import { createApp } from 'vue'
import App from './App'
import router from "@/router/router";
import components from "core-js/stable/dom-collections";
import Vuelidate from 'vuelidate'

const app = createApp(App)

// app.use(Vuelidate);
components.forEach(component => {
    app.component(component.name, component)
})

app
    .use(router)
    .mount('#app')