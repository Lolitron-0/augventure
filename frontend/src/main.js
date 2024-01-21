import { createApp } from 'vue'
import App from './App'
import router from "@/router/router";
import components from "core-js/stable/dom-collections";
import Vuelidate from 'vuelidate'

const app = createApp(App)

<<<<<<< HEAD
// app.use(Vuelidate);
=======
//app.use(Vuelidate);
>>>>>>> e30a13990d76036161a19587e4f2db5dab34e90a
components.forEach(component => {
    app.component(component.name, component)
})

app
    .use(router)
    .mount('#app')