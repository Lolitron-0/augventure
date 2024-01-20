<template>
<!--  :to="{name: 'myEvents'}"-->
  <div class="ProfileNavbar">
    <div class="block_text_navigation">
      <router-link :to="{ name: 'profile' }"
                   :class="{ 'active': isProfileActive, 'rout_nav_text': !isProfileActive}"
      >
        <i class='bx bxs-calendar-event' ></i>
        Events
      </router-link>
    </div>
    <div class="block_text_navigation">
      <router-link :to="{name: 'archive', params: {name: 'archive'}}"
                   :class="{ 'active': isArchiveActive, 'rout_nav_text': !isArchiveActive}"
      >
        <i class="ri-git-repository-line"></i>
        Archive
      </router-link>
    </div>
    <div class="block_text_navigation">
      <router-link :to="{name: 'subscriptions', params: {name: 'subscriptions'}}"
                   :class="{ 'active': isSubscriptionsActive, 'rout_nav_text': !isSubscriptionsActive}"
      >
        <i class="ri-focus-line"></i>
        Subscriptions
      </router-link>
    </div>
    <div class="block_text_navigation">
      <router-link :to="{name: 'settings', params: {name: 'settings'}}"
                   :class="{ 'active': isSettingsActive, 'rout_nav_text': !isSettingsActive}"
      >
        <i class='bx bx-cog' ></i>
        Settings
      </router-link>
    </div>
  </div>
</template>

<script>
export default {
  computed: {
    isProfileActive() {
      return this.$route.name === 'profile';
    },
    isArchiveActive() {
      return this.$route.name === 'archive';
    },
    isSubscriptionsActive() {
      return this.$route.name === 'subscriptions';
    },
    isSettingsActive() {
      return this.$route.name === 'settings';
    },
  },
}
</script>

<style scoped>
@import "@/styles.css";

.ProfileNavbar{
  display: flex;
  justify-content: left;
  gap: 50px;
  border-bottom: 1px solid var(--border-light-gray-color);
  padding: 5px 10px;
  margin-bottom: 5px;
}
.rout_nav_text {
  color: var(--text-wight-color);
  text-decoration: none;
  transition: .3s;
}
.active {
  color: var(--text-turquoise-color);
  text-decoration: none;
  transition: .3s;
}
.rout_nav_text:hover{
  color: var(--text-turquoise-color);
}
.block_text_navigation{
  display: flex;
  flex-direction: row;
  gap: 10px;
  color: var(--text-wight-color);
  padding: 5px;
}

@media (max-width: 992px) {
  .ProfileNavbar{
    gap: 30px;
  }
}

</style>