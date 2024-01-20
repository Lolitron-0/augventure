<template>

  <link href='https://cdnjs.cloudflare.com/ajax/libs/remixicon/4.0.1/remixicon.css' rel='stylesheet'>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>

  <header class="header" id="header">

    <div class="nav_left">
      <i class='bx bx-menu' id="menu-icon" v-if="!show" @click="Show" key="menu"></i>
      <i class='bx bx-x' id="x-icon" v-else @click="Show"></i>
      <router-link class="main_menu_text" :to="{ name: 'home' }">
        <div class="ellipse_nav_logo"></div>
      </router-link>

        <nav class="nav_menu" v-if="show">
          <ul>
            <li><router-link class="main_menu_text" :to="{ name: 'home' }">Home</router-link></li>
            <li><a href="#" class="main_menu_text">Events <i class='bx bx-chevron-down'></i></a>
              <ul>
                <li><router-link :to="{ name: 'newEvents' }">New events</router-link></li>
                <li><router-link :to="{ name: 'currentEvents' }">Current events </router-link></li>
              </ul>
            </li>
            <li><router-link class="main_menu_text" :to="{ name: 'about'}" >About</router-link></li>
          </ul>
        </nav>
    </div>

    <div class="nav_right">
      <div class="search_form_show" v-if="show_search">
        <i class='bx bx-search search_vector' @click="ShowSearch"></i>
        <input class="nav_search_form_text" type="text" placeholder="Search">
      </div>
      <div class="search_form_not_show" v-else>
        <i class='bx bx-search search_vector' @click="ShowSearch"></i>
        <input class="nav_search_form_text" type="text" placeholder="Search">
      </div>

      <router-link :to="{ name: 'notifications' }" style="text-decoration: none"><i class='bx bx-bell bell_vector'></i></router-link>
      <div class="user_logo" @click="ShowSidebar"></div>
    </div>
  </header>
  <aside v-if="!show_sidebar">
      <div class="side_header">
        <div class="side_header_left">
          <div class="ellipse_nav_logo"></div>

          <p class="side_nick">Nickname</p>
        </div>

        <i class='bx bx-x sidebar_x' @click="ShowSidebar"></i>
      </div>
      <div class="side_profile_menu">
        <router-link :to="{ name: 'profile' }" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bxs-user user_vector' ></i>
            <p class="user_text">Your profile</p>
          </my-button>
        </router-link>
        <router-link :to="{ name: 'register' }" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bxs-user-plus user_plus_vector' ></i>
            <p class="user_plus_text">Add account</p>
          </my-button>
        </router-link>
      </div>

      <hr>

      <div class="side_settings_menu">
        <router-link :to="{name: 'settings', params: {name: 'settings'}}" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bxs-cog settings_vector' ></i>
            <p class="settings_text">Settings</p>
          </my-button>
        </router-link>
        <router-link :to="{ name: 'notifications' }" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bxs-bell bell_vector_sidebar' ></i>
            <p class="bell_text_sidebar">Notifications</p>
          </my-button>
        </router-link>
        <router-link :to="{ name: 'updates' }" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bx-news updates_vector' ></i>
            <p class="updates_text">Updates</p>
          </my-button>
        </router-link>
      </div>
    <hr>
      <div class="side_sign_out">
        <router-link :to="{ name: 'login' }" tag="button" style="text-decoration: none">
          <my-button @click="ShowSidebar" class="btn_side">
            <i class='bx bx-log-out sign_out_vector' ></i>
            <p class="sign_out_text">Sign out</p>
          </my-button>
        </router-link>
      </div>
      <div class="augventure_2023">© 2023 Augventure</div>
    </aside>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";

export default {
  components: {MyButton},
  data() {
    return {
      show: true,
      show_search: true,
      show_sidebar: true,
    }
  },
  computed: {
    isMobile() {
      // Определяем, что ширина экрана меньше 768px
      return window.innerWidth <= 768;
    }
  },
  methods: {
    Show() {
      this.show = !this.show;
    },
    ShowSearch() {
      this.show_search = !this.show_search;
    },
    ShowSidebar() {
      this.show_sidebar = !this.show_sidebar;
    },
    // Обработчик события resize
    handleResize() {
      // Если ширина экрана стала больше 768px и бургер-меню скрыто, то показываем меню
      if (window.innerWidth > 768 && !this.show) {
        this.show = true;
      }
    }
  },
  mounted() {
    // Добавляем слушатель события resize для отслеживания изменений ширины экрана
    window.addEventListener('resize', this.handleResize);
  },
  beforeDestroy() {
    // Удаляем слушатель события при уничтожении компонента
    window.removeEventListener('resize', this.handleResize);
  }
}
</script>

<style scoped>

.header {
  width: 100%;
  position: fixed;
  padding: 5px 60px;
  background: #24292F;
  display: flex;
  justify-content: space-between;
  align-items: center;
  left: 0;
  top: 0;
  border-bottom: 2px solid #858585;
  z-index: 1000;
}
.nav_left {
  justify-content: center;
  align-items: center;
  display: flex;
}

.ellipse_nav_logo {
  width: 30px;
  height: 30px;
  border: solid 1px #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 100%;
  margin-right: 20px;
  //flex-shrink: 0;
}
.nav_menu ul li {
  position: relative;
  float: left;
  list-style-type: none;
}

.nav_menu ul li a{
  color: #cfcfcf;
  font-size: 16px;
  transition: .3s;
  display: block;
  padding: 15px;
  text-decoration: none;
}

.nav_menu ul li a:hover{
  color: #31a0a8;
  background: #081b29;
}
.main_menu_text:hover {
  border-radius: 5px;
}
.nav_menu ul li ul{
  position: absolute;
  left: 0;
  width: 180px;
  background: #24292F;
  display: none;
}
.nav_menu ul li ul li{
  width: 100%;
  border: 1px solid rgba(0, 0, 0, .2);
}

.nav_menu ul li ul li ul{
  left: 179px;
  top: 0;
}
.nav_menu ul li:hover > ul {
  display: initial;
}

.nav_right {
  height: 100%;
  display: flex;
  column-gap: 20px;
  align-items: center;
  justify-content: center;
  //flex-shrink: 0;
}
.search_form_show {
  border: 1px solid #cfcfcf;
  display: flex;
  padding: 0 20px 0 5px;
  justify-content: center;
  align-items: center;
  height: 32px;
  width: 260px;
  border-radius: 5px;
  //overflow: hidden;
  transition: .4s ease;
}


.search_form_not_show {
  border: 1px solid #cfcfcf;
  display: flex;
  padding: 0 20px 0 5px;
  justify-content: center;
  align-items: center;
  height: 32px;
  width: 260px;
  border-radius: 5px;
  transition: .4s ease;
}

.nav_search_form_text {
  border: none;
  width: 100%;
  height: 100%;
  outline: none;
  font-size: 16px;
  padding-left: 5px;
  background-color: transparent;
  color: #cfcfcf;
}

.search_vector {
  background-color: transparent;
  color: #cfcfcf;
  font-size: 18px;
  cursor: pointer;
  padding: 5px;
}

.bell_vector::before{
  justify-content: center;
  align-items: center;
  display: flex;
  height: 32px;
  width: 32px;
}
.bell_vector {
  height: 32px;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 5px;
  border: 1px solid #cfcfcf;
  color: #cfcfcf;
  cursor: pointer;
  transition: .3s;
  //flex-shrink: 0;
}
.bell_vector:hover {
  color: #32B8C2;
  border: 1px solid #32B8C2;
}
.user_logo {
  width: 32px;
  height: 32px;
  border: solid 0.1rem #858585;
  box-sizing: border-box;
  background-size: 100% 100%;
  background-repeat: no-repeat;
  background-position: center;
  border-radius: 100%;
  cursor: pointer;
  //flex-shrink: 0;
}

#menu-icon {
  font-size: 32px;
  color: #cfcfcf;
  display: none;
}

#x-icon {
  font-size: 32px;
  color: #cfcfcf;
  display: none;
}

/*///////////////////////SIDEBAR/////////////////////////*/
aside{
  display: flex;
  flex-direction: column;
//padding: 1rem 0rem 3.05rem 0rem;
  width: 20.8%;
  min-width: 250px;
  max-width: 300px;
  min-height: 100vh;
  position: absolute;
  right: 0;
  top: 0;
  overflow: hidden;
  background-color: #24292F;
  color: #cfcfcf;
  border-radius: 10px 0 0 10px;
  transition: 0.2s ease-out;
  z-index: 1000;
}

.side_header {
  padding: 10px 5px 20px 10px;
  display: flex;
  justify-content: space-between;
}

.side_header_left {
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
}

.sidebar_x {
  font-size: 30px;
  cursor: pointer;
}
hr {
  background-color: #0d1117;
  padding: 1px;
  border: #0d1117;
}
.side_profile_menu {
  padding: 0 0 10px 0;
}
.side_settings_menu {

  padding: 10px 0;
}
.side_sign_out {
  padding: 10px 0 0 0;
}

.btn_side {
  border: 1px solid #0d1117;
  width: 100%;
  height: 40px;
  display: flex;
  align-items: center;
  padding: 0;
  border-radius: 0;
  color: #cfcfcf;
  justify-content: left;
  gap: 5px;
}

.user_vector {
  padding-left: 7px;
  font-size: 20px;
}
.user_text {

}

.user_plus_vector {
  padding-left: 7px;
  font-size: 20px;
}
.user_plus_text {

}

.settings_vector {
  padding-left: 7px;
  font-size: 20px;
}
.settings_text {

}

.bell_vector_sidebar {
  padding-left: 7px;
  font-size: 20px;
}
.bell_text_sidebar {

}

.updates_vector {
  padding-left: 7px;
  font-size: 20px;
}
.updates_text {

}

.sign_out_vector {
  padding-left: 7px;
  font-size: 20px;
}
.sign_out_text {

}


.augventure_2023 {
  bottom: 15px;
  position: absolute;
  font-size: 12px;
  left: 15px;
  letter-spacing: 1.5px;
}

@media (max-width: 992px) {
  .header {
    padding: .3rem 4%;
  }
  .search_form_show {
    padding: 0;
    width: 32px;
    transition: .4s;
  }

  .user_vector{
    font-size: 16px;
  }
  .user_text{
    font-size: 12px;
  }

  .user_plus_vector{
    font-size: 16px;
  }
  .user_plus_text{
    font-size: 12px;
  }
  .settings_vector{
    font-size: 16px;
  }
  .settings_text{
    font-size: 12px;
  }
  .bell_vector_sidebar{
     font-size: 16px;
   }
  .bell_text_sidebar{
    font-size: 12px;
  }
  .updates_vector{
    font-size: 16px;
  }
  .updates_text{
    font-size: 12px;
  }
  .sign_out_vector{
    font-size: 16px;
  }
  .sign_out_text{
    font-size: 12px;
  }

  .augventure_2023{
    font-size: 10px;
  }

  .search_vector:hover {
    color: #31a0a8;
  }


}

@media (max-width: 768px) {
  aside{
    width: 300px;
    max-width: 300px;
    font-size: 18px;
  }
  #menu-icon {
    display: block;
    padding-right: 20px;
  }
  #x-icon {
    display: block;
    padding-right: 20px;
  }

  .nav_menu {
    position: absolute;
    top: 102%;
    left: 0;
    width: 100%;
    padding: .5rem 4%;
    background: #24292F;
    border-bottom: 2px solid #858585;
    justify-content: center;
    display: flex;
    flex-direction: column;
  }

  .nav_menu a {
    display: block;
    margin: 1.5rem 0;
  }
  .search_form_show {
    padding: 0;
    width: 32px;
  }
  .search_vector:hover {
    color: #31a0a8;
  }

  .nav_menu ul li {
    float: none;
    padding: 0;
  }

  .nav_menu ul li a{
    display: block;
    text-decoration: none;
    padding: 15px;
    margin: 0;
  }
/*
  .nav_menu ul li a:hover{
    color: #31a0a8;
    background: #081b29;
  }
  .main_menu_text:hover {
    border-radius: 5px;
  }*/
  .nav_menu ul li ul{
    position: relative;
    left: 0;
    width: 100%;
    background: #24292F;
    display: none;
  }
  .nav_menu ul li ul li{
    width: 100%;
    padding: 0 0 0 15px;
    border: none;
  }

  .nav_menu ul li ul li ul{
    left: 0;
  }
  .nav_menu ul li:hover > ul {
    display: initial;
  }


}

@media (max-width: 430px) {
  aside{
    min-width: 100vw;
  }
  .btn_side{
    align-items: center;
    justify-content: center;
  }
}
</style>