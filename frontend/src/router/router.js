import { createRouter, createWebHistory } from 'vue-router'
import Login from '@/pages/Login.vue'
import Register from '@/pages/Register.vue'
import Profile from '@/pages/Profile.vue'
import Home from '@/pages/Home.vue'
import About from '@/pages/About.vue'
import Events from '@/pages/Events.vue'
import Notifications from '@/pages/Notifications.vue'
import Updates from '@/pages/Updates.vue'
import NewEvents from "@/pages/NewEvents.vue";
import CurrentEvents from "@/pages/CurrentEvents.vue";
import Voting from "@/pages/Voting.vue";
import Settings from "@/pages/Settings.vue";
import Archive from "@/pages/Archive.vue"
import MyEvents from "@/pages/MyEvents.vue"
import Subscriptions from "@/pages/Subscriptions.vue";
import NotFound from "@/pages/404.vue";

const routes = [
  {
    path: '/login',
    name: 'login',
    meta: { state: 'empty' },
    component: Login
  },
  {
    path: '/signup',
    name: 'register',
    meta: { state: 'empty' },
    component: Register
  },
  {
    path: '/users/me',
    name: 'profile',
    meta: { state: 'main' },
    component: Profile
  },
  {
    path: '/home',
    name: 'home',
    meta: { state: 'main' },
    component: Home
  },
  {
    path: '/about',
    name: 'about',
    meta: { state: 'main' },
    component: About
  },
  {
    path: '/events',
    name: 'events',
    meta: { state: 'main' },
    component: Events
  },
  {
    path: '/notifications',
    name: 'notifications',
    meta: { state: 'main' },
    component: Notifications
  },
  {
    path: '/updates',
    name: 'updates',
    meta: { state: 'main' },
    component: Updates
  },
  {
    path: '/events/new',
    name: 'newEvents',
    meta: { state: 'main' },
    component: NewEvents
  },
  {
    path: '/events/current',
    name: 'currentEvents',
    meta: { state: 'main' },
    component: CurrentEvents
  },
  {
    path: '/profile/myEvents',
    name: 'myEvents',
    meta: { state: 'main' },
    component: MyEvents
  },
  {
    path: '/users/me/archive',
    name: 'archive',
    meta: { state: 'main' },
    component: Archive
  },
  { 
    path: '/users/me/subscriptions',
    name: 'subscriptions',
    meta: { state: 'main' },
    component: Subscriptions
  },
  {
    path: '/users/me/settings',
    name: 'settings',
    meta: { state: 'main' },
    component: Settings
  },
  {
    path: '/events/current/:id',
    name: 'voting',
    meta: { state: 'main' },
    component: Voting
  },

  // {
  //   path: '*',
  //   name: 'notFound',
  //   meta: { state: 'empty' },
  //   component: NotFound
  // },

]

const router = createRouter({
  routes,
  history: createWebHistory(process.env.BASE_URL),

})

export default router;
